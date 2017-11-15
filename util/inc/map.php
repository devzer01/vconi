<?php

$single = false;

if (isset($argv[1])) $single = $argv[1];

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

foreach($lang_array as $v) {
    if ($single !== false && $v[0] != $single) continue;
    $runner = new Runner($v[0], strtolower($v[3]), strtolower($v[4]));
    $runner->build_map(true);
}