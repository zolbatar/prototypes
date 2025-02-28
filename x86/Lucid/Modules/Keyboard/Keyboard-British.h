bool Kg_nKeyStates[ 128 ];

uchar Kg_nKeyCodes[ 128 ] = {
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_ESCAPE,
                                '1',
                                '2',
                                '3',
                                '4',
                                '5',
                                '6',
                                '7',
                                '8',
                                '9',                                                                                                                                                                                                                       	    // 10
                                '0',
                                '-',
                                '=',
                                KMESSAGE_KEY_BACKSPACE,
                                KMESSAGE_KEY_TAB,
                                'q',
                                'w',
                                'e',
                                'r',
                                't',                                                                                                                                                                                                                       	  // 20
                                'y',
                                'u',
                                'i',
                                'o',
                                'p',
                                '[',
                                ']',
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                'a',                                                                                                                                                                                                                       	       // 30
                                's',
                                'd',
                                'f',
                                'g',
                                'h',
                                'j',
                                'k',
                                'l',
                                ';',
                                '\'',                                                                                                                                                                                                                       	       // 40
                                KMESSAGE_KEY_ENTER,
                                KMESSAGE_KEY_LSHIFT,
                                '#',
                                'z',
                                'x',
                                'c',
                                'v',
                                'b',
                                'n',
                                'm',                                                                                                                                                                                                                       	     // 50
                                ',',
                                '.',
                                '/',
                                KMESSAGE_KEY_RSHIFT,
                                '*',
                                KMESSAGE_KEY_LCTRL,
                                ' ',
                                KMESSAGE_KEY_ALT,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                        // 60
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                        // 70
                                KMESSAGE_KEY_KEYPAD_HOME,
                                KMESSAGE_KEY_KEYPAD_UP,
                                KMESSAGE_KEY_KEYPAD_PGUP,
                                '-',
                                KMESSAGE_KEY_KEYPAD_LEFT,
                                KMESSAGE_KEY_KEYPAD_CENTRE,
                                KMESSAGE_KEY_KEYPAD_RIGHT,
                                '+',
                                KMESSAGE_KEY_KEYPAD_END,
                                KMESSAGE_KEY_KEYPAD_DOWN,                                                                                                                                                                                                                        // 80
                                KMESSAGE_KEY_KEYPAD_PGDN,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                '\\',
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 90
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 100
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 110
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 120
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY,
                                KMESSAGE_KEY_NOKEY
                            };

uchar Kg_nKeyCodesShift[ 128 ] = {
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_ESCAPE,
                                     '!',
                                     '"',
                                     '�',
                                     '$',
                                     '%',
                                     '^',
                                     '&',
                                     '*',
                                     '(',
                                     ')',                                                                                                                                                                                                                       	    // 10
                                     '_',
                                     '+',
                                     KMESSAGE_KEY_BACKSPACE,
                                     KMESSAGE_KEY_TAB,
                                     'Q',
                                     'W',
                                     'E',
                                     'R',
                                     'T',                                                                                                                                                                                                                       	  // 20
                                     'Y',
                                     'U',
                                     'I',
                                     'O',
                                     'P',
                                     '{',
                                     '}',
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     'A',                                                                                                                                                                                                                       	       // 30
                                     'S',
                                     'D',
                                     'F',
                                     'G',
                                     'H',
                                     'J',
                                     'K',
                                     'L',
                                     ':',
                                     '@',                                                                                                                                                                                                                       	       // 40
                                     KMESSAGE_KEY_ENTER,
                                     KMESSAGE_KEY_LSHIFT,
                                     '~',
                                     'Z',
                                     'X',
                                     'C',
                                     'V',
                                     'B',
                                     'N',
                                     'M',                                                                                                                                                                                                                       	     // 50
                                     '<',
                                     '>',
                                     '?',
                                     KMESSAGE_KEY_RSHIFT,
                                     '*',
                                     KMESSAGE_KEY_LCTRL,
                                     ' ',
                                     KMESSAGE_KEY_ALT,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                        // 60
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                        // 70
                                     KMESSAGE_KEY_KEYPAD_HOME,
                                     KMESSAGE_KEY_KEYPAD_UP,
                                     KMESSAGE_KEY_KEYPAD_PGUP,
                                     '-',
                                     KMESSAGE_KEY_KEYPAD_LEFT,
                                     KMESSAGE_KEY_KEYPAD_CENTRE,
                                     KMESSAGE_KEY_KEYPAD_RIGHT,
                                     '+',
                                     KMESSAGE_KEY_KEYPAD_END,
                                     KMESSAGE_KEY_KEYPAD_DOWN,                                                                                                                                                                                                                        // 80
                                     KMESSAGE_KEY_KEYPAD_PGDN,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     '|',
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 90
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 100
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 110
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,                                                                                                                                                                                                                           // 120
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY,
                                     KMESSAGE_KEY_NOKEY
                                 };


