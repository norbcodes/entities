// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file colors.hpp
 * \author norbcodes
 * \brief Colors! And styles!（人´∀`*）
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \details These are graphical ANSI escape codes, which can be used in fmt::print<br>
 *          or fmt::format to colorize or stylize text.
 * \note These won't work if code is compiled without <b>\_\_ENTITIES2_COLORS\_\_</b><br>
 * \note By default, colors are in RGB. Using <b>\_\_ENTITIES2_4_BIT_COLORS\_\_</b> forces the game<br>
 *       to use predefined terminal colors.<br>
 * \note In 4bit mode, styling is turned off by default. Use <b>\_\_ENTITIES2_4_BIT_STYLES\_\_</b> to turn it<br>
 *       on.<br>
 * \note Use <b>\_\_ENTITIES2_4_BIT_AIXTERM\_\_</b> to enable bright colors.<br>
 */

#pragma once

// COLOR/STYLE MACROS
#ifdef __ENTITIES2_COLORS__
    #ifndef __ENTITIES2_4_BIT_COLORS__
        // RESET
        #define RESET               "\x1b[0m"
        // STYLES
        #define BOLD                "\x1b[1m"
        #define FAINT               "\x1b[2m"
        #define ITALIC              "\x1b[3m"
        #define UNDERLINE           "\x1b[4m"
        #define BLINKING            "\x1b[5m"
        // TEXT COLORS
        #define RED                 "\x1b[38;2;255;25;25m"
        #define BLUE                "\x1b[38;2;36;80;255m"
        #define ORANGE              "\x1b[38;2;230;153;0m"
        #define WHITE               "\x1b[38;2;230;230;230m"
        #define HOT_PINK            "\x1b[38;2;153;0;77m"
        #define GRAY                "\x1b[38;2;99;99;99m"
        #define DARK_GRAY           "\x1b[38;2;68;68;68m"
        #define PINK                "\x1b[38;2;234;128;255m"
        #define GOLD                "\x1b[38;2;255;195;77m"
        #define GREEN               "\x1b[38;2;0;255;42m"
        #define PURPLE              "\x1b[38;2;76;0;230m"
        #define DARK_GREEN          "\x1b[38;2;181;196;27m"
        #define LAVENDER            "\x1b[38;2;187;153;255m"
        #define YELLOW              "\x1b[38;2;255;255;38m"
        #define TEAL                "\x1b[38;2;0;130;181m"
        #define BROWN               "\x1b[38;2;153;77;0m"
        #define BLACK               "\x1b[38;2;0;0;0m"
        // BACKGROUND COLORS
        #define WHITE_BACKGROUND    "\x1b[48;2;230;230;230m"
    #else // __ENTITIES2_4_BIT_COLORS__
        #define RESET               "\x1b[0m"

        #ifdef __ENTITIES2_4_BIT_STYLES__
            #define BOLD                "\x1b[1m"
            #define FAINT               "\x1b[2m"
            #define ITALIC              "\x1b[3m"
            #define UNDERLINE           "\x1b[4m"
            #define BLINKING            "\x1b[5m"
        #else // __ENTITIES2_4_BIT_STYLES__
            #define BOLD                ""
            #define FAINT               ""
            #define ITALIC              ""
            #define UNDERLINE           ""
            #define BLINKING            ""
        #endif // __ENTITIES2_4_BIT_STYLES__

        #ifdef __ENTITIES2_4_BIT_AIXTERM__
            #define RED                 "\x1b[31m"
            #define BLUE                "\x1b[34m"
            #define ORANGE              "\x1b[33m"
            #define WHITE               "\x1b[37m"
            #define HOT_PINK            "\x1b[95m"
            #define GRAY                "\x1b[37m"
            #define DARK_GRAY           "\x1b[90m"
            #define PINK                "\x1b[35m"
            #define GOLD                "\x1b[93m"
            #define GREEN               "\x1b[32m"
            #define PURPLE              "\x1b[35m"
            #define DARK_GREEN          "\x1b[32m"
            #define LAVENDER            "\x1b[36m"
            #define YELLOW              "\x1b[33m"
            #define TEAL                "\x1b[96m"
            #define BROWN               "\x1b[33m"
            #define BLACK               "\x1b[30m"
            #define WHITE_BACKGROUND    "\x1b[47m"
        #else // __ENTITIES2_4_BIT_AIXTERM__
            #define RED                 "\x1b[31m"
            #define BLUE                "\x1b[34m"
            #define ORANGE              "\x1b[33m"
            #define WHITE               "\x1b[37m"
            #define HOT_PINK            "\x1b[35m"
            #define GRAY                "\x1b[37m"
            #define DARK_GRAY           "\x1b[37m"
            #define PINK                "\x1b[35m"
            #define GOLD                "\x1b[33m"
            #define GREEN               "\x1b[32m"
            #define PURPLE              "\x1b[35m"
            #define DARK_GREEN          "\x1b[32m"
            #define LAVENDER            "\x1b[36m"
            #define YELLOW              "\x1b[33m"
            #define TEAL                "\x1b[36m"
            #define BROWN               "\x1b[33m"
            #define BLACK               "\x1b[30m"
            #define WHITE_BACKGROUND    "\x1b[47m"
        #endif // __ENTITIES2_4_BIT_AIXTERM__

    #endif // __ENTITIES2_4_BIT_COLORS__
#else // __ENTITIES2_COLORS__
    #define RESET               ""
    #define BOLD                ""
    #define FAINT               ""
    #define ITALIC              ""
    #define UNDERLINE           ""
    #define BLINKING            ""
    #define RED                 ""
    #define BLUE                ""
    #define ORANGE              ""
    #define WHITE               ""
    #define HOT_PINK            ""
    #define GRAY                ""
    #define DARK_GRAY           ""
    #define PINK                ""
    #define GOLD                ""
    #define GREEN               ""
    #define PURPLE              ""
    #define DARK_GREEN          ""
    #define LAVENDER            ""
    #define YELLOW              ""
    #define TEAL                ""
    #define BROWN               ""
    #define BLACK               ""
    #define WHITE_BACKGROUND    ""
#endif // __ENTITIES2_COLORS__

/** 
 * \def RESET
 * \brief If used, resets all colors and styling. 
 * \hideinitializer
 */

/**
 * \def BOLD
 * \brief <b>Bold</b> text styling. <span style="background-color: rgb(0, 0, 0);"><b>\#\#\#TEST\#\#\#</b></span>
 * \hideinitializer
 */

/**
 * \def FAINT
 * \brief Faint text styling.
 * \warning Isn't supported by most terminals.
 * \hideinitializer
 */

/**
 * \def ITALIC
 * \brief <i>Italic</i> text styling. <span style="background-color: rgb(0, 0, 0);"><i>\#\#\#TEST\#\#\#</i></span>
 * \hideinitializer
 */

/**
 * \def UNDERLINE
 * \brief <u>Underline</u> text styling. <span style="background-color: rgb(0, 0, 0);"><u>\#\#\#TEST\#\#\#</u></span>
 * \hideinitializer
 */

/**
 * \def BLINKING
 * \brief Blinking text styling.
 * \warning Isn't supported by most terminals.
 * \hideinitializer
 */

/**
 * \def RED
 * \brief RGB value = 255,25,0 <span style="background-color: rgb(0, 0, 0);color: rgb(255, 25, 0)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def BLUE
 * \brief RGB value = 36,80,255 <span style="background-color: rgb(0, 0, 0);color: rgb(36, 80, 255)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def ORANGE
 * \brief RGB value = 230,153,0 <span style="background-color: rgb(0, 0, 0);color: rgb(230, 153, 0)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def WHITE
 * \brief RGB value = 230,230,230 <span style="background-color: rgb(0, 0, 0);color: rgb(230, 230, 230)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def HOT_PINK
 * \brief RGB value = 153,0,77 <span style="background-color: rgb(0, 0, 0);color: rgb(153, 0, 77)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def GRAY
 * \brief RGB value = 99,99,99 <span style="background-color: rgb(0, 0, 0);color: rgb(99, 99, 99)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def DARK_GRAY
 * \brief RGB value = 68,68,68 <span style="background-color: rgb(0, 0, 0);color: rgb(68, 68, 68)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def PINK
 * \brief RGB value = 234,128,255 <span style="background-color: rgb(0, 0, 0);color: rgb(234, 128, 255)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def GOLD
 * \brief RGB value = 255,195,77 <span style="background-color: rgb(0, 0, 0);color: rgb(255, 195, 77)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def GREEN
 * \brief RGB value = 0,255,42 <span style="background-color: rgb(0, 0, 0);color: rgb(0, 255, 42)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def PURPLE
 * \brief RGB value = 76,0,230 <span style="background-color: rgb(0, 0, 0);color: rgb(76, 0, 230)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def DARK_GREEN
 * \brief RGB value = 181,196,27 <span style="background-color: rgb(0, 0, 0);color: rgb(181, 196, 27)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def LAVENDER
 * \brief RGB value = 187,153,255 <span style="background-color: rgb(0, 0, 0);color: rgb(187, 153, 255)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def YELLOW
 * \brief RGB value = 255,255,38 <span style="background-color: rgb(0, 0, 0);color: rgb(255, 255, 38)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def TEAL
 * \brief RGB value = 0,130,181 <span style="background-color: rgb(0, 0, 0);color: rgb(0, 130, 181)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def BROWN
 * \brief RGB value = 153,77,0 <span style="background-color: rgb(0, 0, 0);color: rgb(153, 77, 0)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def BLACK
 * \brief RGB value = 0,0,0 <span style="background-color: rgb(255, 255, 255);color: rgb(0, 0, 0)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

/**
 * \def WHITE_BACKGROUND
 * \brief RGB value = 0,0,0 <span style="background-color: rgb(255, 255, 255);color: rgb(0, 0, 0)">\#\#\#TEST\#\#\#</span>
 * \hideinitializer
 */

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0