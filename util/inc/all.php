<?php

require_once "mapread.php";

$lang_array = [
	['0xF','0B00','0B7F','Odia', 'odi'],
	['0x1','980','9FF','Assamese', 'asm'],
	['0x3','980','9FF','Bengali', 'ben'],
	['0x6','900','97F','Devanagari', 'dev'],
	['0x7','A80','AFF','Gujarati', 'guj'],
	['0x8','A00','A7F','Gurmukhi', 'gur'],
	['0x16','0F00','0FFF','Tibetan', 'tib'],
	['0x4','11000','1107F','Brahmi', 'bra'],
	['0x14','0C00','0C7F','Telugu', 'tlg'],
	['0xA','0C80','0CFF','Kannada', 'kan'],
	['0x10','0D80','0DFF','Sinhala', 'sin'],
	['0xE','0D00','0D7F','Malayalam', 'mal'],
	['0x13','0B80','0BFF','Tamil', 'tam'],
	['0x5','1000','104F','Burmese', 'bur'],
	['0xB','1780','17FF','Khmer', 'khm'],
	['0x15','E00','0E7F','Thai', 'thi'],
	['0xC','E80','EFF','Lao', 'lao'],
	['0x2','1B00','1B7F','Balinese', 'bal'],
	['0x9','A980','A9DF','Javanese', 'jav'],
	['0x11','1B80','1BFF','Sundanese', 'sud'],
	['0XD','1A00','1A7F','Lontara', 'lon']
];

$struct1 = "typedef struct b8e_config {\n";
$includes = [];
$m = [];
foreach($lang_array as $v) {
    $runner = new Runner($v[0], strtolower($v[3]), strtolower($v[4]));
    $runner->build_map(false);
    $runner->format_header("../../src/lang/" . strtolower($v[3]) . ".h");
    $m[] = sprintf("\tconst unsigned char *%s;", strtolower($v[3]));
    $includes[] = sprintf("#include \"%s.h\"", strtolower($v[3]));
}
$struct2 = "\n} b8e_config;\n";

file_put_contents("../../src/vconi_gen.h", $struct1 . implode("\n", $m) . $struct2);

$load = "b8e_map *map_load(b8e_config *config, LANGUAGE lang, b8e_map *map) {\n\tswitch (lang) {\n\t\tcase L_BASE:\n\t\t\tbreak;\n";

$init = "b8e_map *map_init(b8e_config *config) {\n\tb8e_map *map = (b8e_map *) malloc(sizeof(b8e_map));\n";
foreach($lang_array as $v) {
    $init .= "\tconfig->" . strtolower($v[3]) . " = (const unsigned char *) &" . strtolower($v[4]) . "_config;\n";
    $load .= "\t\tcase L_" . strtoupper($v[3]) . ":\n\t\t\tmap = map_parse(config->" . strtolower($v[3]) .", map);\n\t\t\tbreak;\n";
}
$init .= "};\n";
$load .= "\t}\n\treturn map;\n}\n";

file_put_contents("../../src/map/charmap_gen.h", implode("\n", $includes) . "\n\n" . $init . "\n" . $load);


