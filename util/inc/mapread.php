<?php

define("C_LANG", "A");
define("C_START", "B");
define("C_END", "C");
define("C_NAME", "D");
define("R_CLASS", 1);
define("R_CLCODE", 2);

class ucd {

    public $sheet = [];

    protected $index = [
        'punch' => []
    ];

    protected $langs = [
        ['0x1', '980', '9FF'],
        ['0x3', '980', '9FF'],
        ['0x6', '900', '97F'],
        ['0x7', 'A80', 'AFF'],
        ['0xF', '0B00', '0B7F'],
        ['0x8', 'A00', 'A7F'],
        ['0x16', '0F00', '0FFF'],
        ['0x12', 'A800', 'A82F'],
        ['0x4', '11000', '1107F'],
        ['0x14', '0C00', '0C7F'],
        ['0xA', '0C80', '0CFF'],
        ['0x10', '0D80', '0DFF'],
        ['0xE', '0D00', '0D7F'],
        ['0x13', '0B80', '0BFF'],
        ['0x5', '1000', '104F'],
        ['0xB', '1780', '17FF'],
        ['0x15', '0E00', '0E7F'],
        ['0xC', 'E80', 'EFF'],
        ['0x2', '1B00', '1B7F'],
        ['0x9', 'A980', 'A9DF'],
        ['0x11', '1B80', '1BFF'],
        ['0xD', '1A00', '1A1F']
    ];


    public function __construct()
    {
        $fp = fopen("../conf/UnicodeData.txt", "r");
        while (FALSE != ($row = fgetcsv($fp, 0, ";"))) {
            $idx = strtoupper(dechex(hexdec($row[0])));
            $this->sheet[$idx] = $row;
            switch ($row[2]) {
                case "Po":
                    $this->index['punch'][$idx] = $row;
                    break;
            }
        }
        fclose($fp);
    }

    public function get_punch($langs = [])
    {
        $retval = [];
        foreach ($this->index['punch'] as $p => $r) {
            foreach ($this->langs as $l) {
                if (!empty($langs) && !in_array($l[0], $langs)) continue;
                if (hexdec($p) >= hexdec($l[1]) && hexdec($p) <= hexdec($l[2])) {
                    $retval[] = $r;
                }
            }
        }

        return $retval;
    }

    public function codepoint($codepoint)
    {
        return isset($this->sheet[$codepoint]);
    }

    public function item($codepoint)
    {
        return isset($this->sheet[$codepoint]) ? $this->sheet[$codepoint] : -1;
    }
}

class tmap {

    protected $fp = null;

    protected $sheet = [];

    protected $rows = 0;

    protected $cols = 0;

    protected $datastart = "E";

    protected $datacols = [];

    protected $class_header = [];

    protected $byte_map = [];

    protected $range_start = 0;

    protected $range_end = 0;

    public function __construct()
    {

    }



    public function load()
    {
        $fp = fopen("../conf/map2.csv", "r");
        while (FALSE != ($row = fgetcsv($fp))) {
            $this->sheet[] = $row;
        }
        fclose($fp);
        $this->rows = count($this->sheet);
        $this->cols = count($this->sheet[0]);

        $this->class_header = $this->cl_load(R_CLASS);
        $this->byte_map = $this->cl_load(R_CLCODE);
        return [$this->rows, $this->cols];
    }

    public function langs()
    {
        $start = 3; $end = 24;
        $lrec = [];
        for ($i = $start; $i <= $end; $i++) {
            $lrec[] = [$this->cell($i, C_LANG), $this->cell($i, C_START), $this->cell($i, C_END)];
        }
        return $lrec;
    }

    public function r_load($row, $offset = 0)
    {
        $cl = [];
        for ($i = $this->col2num($this->datastart), $idx = $offset; $i < ($this->col2num($this->datastart) + $this->cols - 4); $i++, $idx++) {
            $col = $this->num2col($i);
            $val = $this->cell($row, $col);
            if ($val != "") {
                $cl[$idx] = $val;
            }
            //printf(" # %d => %s === %s\n", $i, $col, $val);
        }
        return $cl;
    }

    public function cl_load($row)
    {
        $a = $this->r_load($row);
        //ksort($a);
        return $a;
    }

    public function get_header()
    {
        return [$this->class_header, $this->byte_map];
    }

    public function num2col($num)
    {
        if ($num < 26) {
            return chr($num + 65);
        } else {
            return chr(64 + ($num / 26)) . chr(65 + ($num % 26));
        }
    }

    public function col2num($col)
    {
        $c_col = ord($col[0]) - 65;
        if (strlen(trim($col)) === 2) {
            $c_col = ord($col[1]) - 65 + (26 * ($c_col + 1));
        }
        return $c_col;
    }

    public function find_lang_record($lang)
    {
        $cs = -1; $vr = -1;
        for ($i = R_CLCODE + 1; $i <= $this->rows; $i++) {
            if ($this->cell($i, C_LANG) == $lang) {
                $cs = $i;
                break;
            }
        }
        return $cs;
    }

    public function get_map_with_meta($lang)
    {
        $lang = $this->get_lang_map($lang);

        $retval = [];
        foreach($this->class_header as $idx => $cls) {
            $record = [];
            if ($lang[$idx] == 0) {
            } else {
                $record = [$cls, $this->byte_map[$idx], $lang[$idx], $idx, "&#x" . dechex($lang[$idx]) . ";"];
                $idx2 = strtoupper(dechex($record[2]));
                $retval[$idx2] = $record;
            }


        }
        return $retval;
    }

    public function get_range($lang) {
        $this->seek_lang($lang);
        return [$this->range_start, $this->range_end];
    }

    protected function seek_lang($lang) {
        $cs = $this->find_lang_record($lang);
        if ($cs == -1) {
            printf("language not found\n");
            exit;
        }
        $this->range_start = hexdec($this->cell($cs, C_START));
        $this->range_end = hexdec($this->cell($cs,C_END));

        return $cs;
    }

    public function get_lang_map($lang) {
        $cs = $this->seek_lang($lang);
        return $this->cl_load($cs);
    }

    public function num2point($num)
    {
        if (hexdec(dechex($num)) !== $num) {
            throw new Exception("none decimal value " . $num);
        }
        return strtoupper(dechex($num));
    }

    public function cell($row, $col)
    {
        $c_col = $this->col2num($col);
        //debug_print_backtrace();
        return isset($this->sheet[--$row][$c_col]) ? $this->sheet[$row][$c_col] : debug_print_backtrace();
    }
}

class Runner {
    
    private $ucd = null;
    
    private $cons = [];
    
    private $range = [];
    
    private $mapper = null;
    
    private $data = [];

    private $header = [];

    private $rows = 0;

    private $cols = 0;

    private $name = "";

    private $version = 0x1;

    private $code = "";

    public function __construct($LANG, $name, $code)
    {
        $this->ucd = new ucd();
        $this->mapper = new tmap();
        list($this->rows, $this->cols) = $this->mapper->load();
        $this->header = $this->mapper->get_header();
        $this->cons = $this->mapper->get_lang_map($LANG);
        $this->range = $this->mapper->get_range($LANG);
        $this->name = $name;
        $this->code = $code;
    }

    function frmt($inp) {
        return str_pad(strtoupper(dechex($inp)), 2, "0", STR_PAD_LEFT);
    }
    
    public function build_map($debug = false)
    {
        $fp = fopen("php://stderr", "w");
        $this->data[0] = [$this->range[0], $this->range[1]];
        for ($i = $this->range[0]; $i < $this->range[1]; $i++) {
            $point = $this->mapper->num2point($i);
            if ($this->ucd->codepoint($point) == 1) {
                $comment = "";
                $meta = $this->ucd->item($point);
                $index = array_search($i, $this->cons);
                if ($index === FALSE) {
                    $mark = "*";
                    if ($meta[2][0] == "M") $mark = "'";
                    else if ($meta[2][0] == "P") $mark = ".";
                    else if ($meta[2][0] == "N") $mark = "#";
                    else if ($meta[2][0] == "S") $mark = "%";
                    $comment = sprintf("%s %d %s %s %d", $meta[0], hexdec($meta[0]), $meta[2], $meta[1], $index);
                    if ($debug) fprintf($fp, "%s %s * * * \n", $mark, $comment);
                } else {
                    $comment = str_pad(sprintf("%s %s ", $meta[0], $this->header[0][$index]), 18, " ",STR_PAD_RIGHT) ;
                    $comment = sprintf("%s %s %d %s ", $comment, $meta[1], hexdec($meta[0]), $meta[2]);
                    if ($debug) fprintf($fp, "+ %s , %s, %s\n", $comment, $this->header[1][$index], dechex($this->cons[$index]));
                }
                $ofs = hexdec($meta[0]);
                $oidx = ($ofs - $this->range[0]);
                $this->data[$oidx + 1] = [$this->header[1][$index], dechex($oidx + ($this->range[0] & 0xff)), 0x00, 0x00, $comment];
            } else {
                if (array_search($i, $this->cons) !== FALSE) {
                    fprintf($fp,"- unknown mapping found at %d %s \n", $i, dechex($i));
                }
            }
        }

        fclose($fp);
    }


    public function format_header($f = "php://stdout")
    {
        $start_r1 = ($this->data[0][0] >> 8);
        $start_r2 = ($this->data[0][0] & 0x00ff);
        $size = $this->data[0][1] - $this->data[0][0];
        $fp = fopen($f, "w");
        $mark = ",";
        //$end_r1 = ($this->data[0][1] >> 8);
        //$end_r2 = ($this->data[0][1] & 0x00ff);
        $header = sprintf("#ifndef VCONI_%s_H\n#define VCONI_%s_H\n\n", $this->name, $this->name);
        fprintf($fp, $header);
        fprintf($fp, "const unsigned char %s_config[%d] = { 0x%s, 0x%s, 0x%s, 0x%s,\n", strtolower($this->code), ($size + 2) * 4, $this->frmt($start_r1), $this->frmt($start_r2), $this->frmt($size), $this->version);
        for ($i = 1; $i < count($this->data); $i++) {
            if ($i === count($this->data) - 1) $mark = "";
            if (isset($this->data[$i])) {
                $v = $this->data[$i];
                fprintf($fp,"0x%s, 0x%s, 0x00, 0x00%s //%s\n", $this->frmt($v[0]), $this->frmt($v[1]), $mark, $v[4]);
            } else {
                fprintf($fp,"0x00, 0x00, 0x00, 0x00%s //%s\n", $mark, "reserved-space");
            }
        }
        fprintf($fp, "%s\n", '};');
        fprintf($fp, "#endif");
        fclose($fp);
    }
}
