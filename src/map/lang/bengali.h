#ifndef VCONI_bengali_H
#define VCONI_bengali_H

const unsigned char ben_config[516] = { 0x09, 0x80, 0x7F, 0x1,
0x80, 0x80, 0x00, 0x00, //0980 2432 Lo BENGALI ANJI 0
0x80, 0x81, 0x00, 0x00, //0981 2433 Mn BENGALI SIGN CANDRABINDU 0
0xCD, 0x82, 0x00, 0x00, //0982 SS ANUSVARA   BENGALI SIGN ANUSVARA 2434 Mc 
0xED, 0x83, 0x00, 0x00, //0983 SS VISARGA    BENGALI SIGN VISARGA 2435 Mc 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0x85, 0x00, 0x00, //0985 SVI A         BENGALI LETTER A 2437 Lo 
0x88, 0x86, 0x00, 0x00, //0986 SVI AA        BENGALI LETTER AA 2438 Lo 
0x82, 0x87, 0x00, 0x00, //0987 SVI I         BENGALI LETTER I 2439 Lo 
0x8A, 0x88, 0x00, 0x00, //0988 SVI II        BENGALI LETTER II 2440 Lo 
0x83, 0x89, 0x00, 0x00, //0989 SVI U         BENGALI LETTER U 2441 Lo 
0x8B, 0x8A, 0x00, 0x00, //098A SVI UU        BENGALI LETTER UU 2442 Lo 
0x84, 0x8B, 0x00, 0x00, //098B SVI VOC R     BENGALI LETTER VOCALIC R 2443 Lo 
0x85, 0x8C, 0x00, 0x00, //098C SVI VOC L     BENGALI LETTER VOCALIC L 2444 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x86, 0x8F, 0x00, 0x00, //098F SVI E         BENGALI LETTER E 2447 Lo 
0x8E, 0x90, 0x00, 0x00, //0990 SVI AI        BENGALI LETTER AI 2448 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xA7, 0x93, 0x00, 0x00, //0993 SVI OO        BENGALI LETTER O 2451 Lo 
0x8F, 0x94, 0x00, 0x00, //0994 SVI AU        BENGALI LETTER AU 2452 Lo 
0x90, 0x95, 0x00, 0x00, //0995 SVD A         BENGALI LETTER KA 2453 Lo 
0xC0, 0x96, 0x00, 0x00, //0996 SC KHA        BENGALI LETTER KHA 2454 Lo 
0xB1, 0x97, 0x00, 0x00, //0997 SC GA         BENGALI LETTER GA 2455 Lo 
0xC1, 0x98, 0x00, 0x00, //0998 SC GHA        BENGALI LETTER GHA 2456 Lo 
0xBD, 0x99, 0x00, 0x00, //0999 SC NGA        BENGALI LETTER NGA 2457 Lo 
0xB2, 0x9A, 0x00, 0x00, //099A SC CA         BENGALI LETTER CA 2458 Lo 
0xC2, 0x9B, 0x00, 0x00, //099B SC CHA        BENGALI LETTER CHA 2459 Lo 
0xB3, 0x9C, 0x00, 0x00, //099C SC JA         BENGALI LETTER JA 2460 Lo 
0xC3, 0x9D, 0x00, 0x00, //099D SC JHA        BENGALI LETTER JHA 2461 Lo 
0xCF, 0x9E, 0x00, 0x00, //099E SC YHA        BENGALI LETTER NYA 2462 Lo 
0xB4, 0x9F, 0x00, 0x00, //099F SC TTA        BENGALI LETTER TTA 2463 Lo 
0xC4, 0xA0, 0x00, 0x00, //09A0 SC TTHA       BENGALI LETTER TTHA 2464 Lo 
0xB5, 0xA1, 0x00, 0x00, //09A1 SC DDA        BENGALI LETTER DDA 2465 Lo 
0xC5, 0xA2, 0x00, 0x00, //09A2 SC DDHA       BENGALI LETTER DDHA 2466 Lo 
0xC6, 0xA3, 0x00, 0x00, //09A3 SC NHA        BENGALI LETTER NNA 2467 Lo 
0xB7, 0xA4, 0x00, 0x00, //09A4 SC TA         BENGALI LETTER TA 2468 Lo 
0xC7, 0xA5, 0x00, 0x00, //09A5 SC THA        BENGALI LETTER THA 2469 Lo 
0xB8, 0xA6, 0x00, 0x00, //09A6 SC DA         BENGALI LETTER DA 2470 Lo 
0xC8, 0xA7, 0x00, 0x00, //09A7 SC DHA        BENGALI LETTER DHA 2471 Lo 
0xB6, 0xA8, 0x00, 0x00, //09A8 SC NA         BENGALI LETTER NA 2472 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0xB9, 0xAA, 0x00, 0x00, //09AA SC PA         BENGALI LETTER PA 2474 Lo 
0xC9, 0xAB, 0x00, 0x00, //09AB SC PHA        BENGALI LETTER PHA 2475 Lo 
0xBA, 0xAC, 0x00, 0x00, //09AC SC BA         BENGALI LETTER BA 2476 Lo 
0xCA, 0xAD, 0x00, 0x00, //09AD SC BHA        BENGALI LETTER BHA 2477 Lo 
0xE2, 0xAE, 0x00, 0x00, //09AE SC MA         BENGALI LETTER MA 2478 Lo 
0xBF, 0xAF, 0x00, 0x00, //09AF SC YA         BENGALI LETTER YA 2479 Lo 
0xBE, 0xB0, 0x00, 0x00, //09B0 SC RA         BENGALI LETTER RA 2480 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0xBB, 0xB2, 0x00, 0x00, //09B2 SC LA         BENGALI LETTER LA 2482 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xCC, 0xB6, 0x00, 0x00, //09B6 SC SHA        BENGALI LETTER SHA 2486 Lo 
0xDC, 0xB7, 0x00, 0x00, //09B7 SC SSHA       BENGALI LETTER SSA 2487 Lo 
0xBC, 0xB8, 0x00, 0x00, //09B8 SC SA         BENGALI LETTER SA 2488 Lo 
0xE1, 0xB9, 0x00, 0x00, //09B9 SC HA         BENGALI LETTER HA 2489 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0xBC, 0x00, 0x00, //09BC 2492 Mn BENGALI SIGN NUKTA 0
0x80, 0xBD, 0x00, 0x00, //09BD 2493 Lo BENGALI SIGN AVAGRAHA 0
0x98, 0xBE, 0x00, 0x00, //09BE SVD AA        BENGALI VOWEL SIGN AA 2494 Mc 
0x92, 0xBF, 0x00, 0x00, //09BF SVD I         BENGALI VOWEL SIGN I 2495 Mc 
0x9A, 0xC0, 0x00, 0x00, //09C0 SVD II        BENGALI VOWEL SIGN II 2496 Mc 
0x93, 0xC1, 0x00, 0x00, //09C1 SVD U         BENGALI VOWEL SIGN U 2497 Mn 
0x9B, 0xC2, 0x00, 0x00, //09C2 SVD UU        BENGALI VOWEL SIGN UU 2498 Mn 
0x94, 0xC3, 0x00, 0x00, //09C3 SVD VOC R     BENGALI VOWEL SIGN VOCALIC R 2499 Mn 
0x8C, 0xC4, 0x00, 0x00, //09C4 SVI VOC RR    BENGALI VOWEL SIGN VOCALIC RR 2500 Mn 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x96, 0xC7, 0x00, 0x00, //09C7 SVD E         BENGALI VOWEL SIGN E 2503 Mc 
0x9E, 0xC8, 0x00, 0x00, //09C8 SVD AI        BENGALI VOWEL SIGN AI 2504 Mc 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xAF, 0xCB, 0x00, 0x00, //09CB SVD OO        BENGALI VOWEL SIGN O 2507 Mc 
0x9F, 0xCC, 0x00, 0x00, //09CC SVD AU        BENGALI VOWEL SIGN AU 2508 Mc 
0x80, 0xCD, 0x00, 0x00, //09CD 2509 Mn BENGALI SIGN VIRAMA 0
0xB7, 0xCE, 0x00, 0x00, //09CE SDC TA        BENGALI LETTER KHANDA TA 2510 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0xD7, 0x00, 0x00, //09D7 2519 Mc BENGALI AU LENGTH MARK 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xCE, 0xDC, 0x00, 0x00, //09DC SC RHA        BENGALI LETTER RRA 2524 Lo 
0xE1, 0xDD, 0x00, 0x00, //09DD SDC HA        BENGALI LETTER RHA 2525 Lo 
0x00, 0x00, 0x00, 0x00 //reserved-space
};
#endif