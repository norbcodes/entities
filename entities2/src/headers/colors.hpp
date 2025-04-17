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
        #define LIGHT_BLUE          "\x1b[38;2;102;230;255m"
        #define ALMOND              "\x1b[38;2;255;238;204m"
        #define CRIMSON             "\x1b[38;2;179;0;30m"
        #define AQUA                "\x1b[38;2;25;255;255m"
        #define DARK_PURPLE         "\x1b[38;2;38;0;77m"
        #define ONYX                "\x1b[38;2;23;22;22m"
        // BACKGROUND COLORS
        #define BG_RED              "\x1b[48;2;255;25;25m"
        #define BG_BLUE             "\x1b[48;2;36;80;255m"
        #define BG_ORANGE           "\x1b[48;2;230;153;0m"
        #define BG_WHITE            "\x1b[48;2;230;230;230m"
        #define BG_HOT_PINK         "\x1b[48;2;153;0;77m"
        #define BG_GRAY             "\x1b[48;2;99;99;99m"
        #define BG_DARK_GRAY        "\x1b[48;2;68;68;68m"
        #define BG_PINK             "\x1b[48;2;234;128;255m"
        #define BG_GOLD             "\x1b[48;2;255;195;77m"
        #define BG_GREEN            "\x1b[48;2;0;255;42m"
        #define BG_PURPLE           "\x1b[48;2;76;0;230m"
        #define BG_DARK_GREEN       "\x1b[48;2;181;196;27m"
        #define BG_LAVENDER         "\x1b[48;2;187;153;255m"
        #define BG_YELLOW           "\x1b[48;2;255;255;38m"
        #define BG_TEAL             "\x1b[48;2;0;130;181m"
        #define BG_BROWN            "\x1b[48;2;153;77;0m"
        #define BG_BLACK            "\x1b[48;2;0;0;0m"
        #define BG_LIGHT_BLUE       "\x1b[48;2;102;230;255m"
        #define BG_ALMOND           "\x1b[48;2;255;238;204m"
        #define BG_CRIMSON          "\x1b[48;2;179;0;30m"
        #define BG_AQUA             "\x1b[48;2;25;255;255m"
        #define BG_DARK_PURPLE      "\x1b[48;2;38;0;77m"
        #define BG_ONYX             "\x1b[48;2;23;22;22m"
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
            #define LIGHT_BLUE          "\x1b[94m"
            #define ALMOND              "\x1b[37m"
            #define CRIMSON             "\x1b[31m"
            #define AQUA                "\x1b[96m"
            #define DARK_PURPLE         "\x1b[35m"
            #define ONYX                "\x1b[90m"

            #define BG_RED              "\x1b[41m"
            #define BG_BLUE             "\x1b[44m"
            #define BG_ORANGE           "\x1b[43m"
            #define BG_WHITE            "\x1b[47m"
            #define BG_HOT_PINK         "\x1b[105m"
            #define BG_GRAY             "\x1b[47m"
            #define BG_DARK_GRAY        "\x1b[100m"
            #define BG_PINK             "\x1b[45m"
            #define BG_GOLD             "\x1b[103m"
            #define BG_GREEN            "\x1b[42m"
            #define BG_PURPLE           "\x1b[45m"
            #define BG_DARK_GREEN       "\x1b[42m"
            #define BG_LAVENDER         "\x1b[46m"
            #define BG_YELLOW           "\x1b[43m"
            #define BG_TEAL             "\x1b[106m"
            #define BG_BROWN            "\x1b[43m"
            #define BG_BLACK            "\x1b[40m"
            #define BG_LIGHT_BLUE       "\x1b[104m"
            #define BG_ALMOND           "\x1b[47m"
            #define BG_CRIMSON          "\x1b[41m"
            #define BG_AQUA             "\x1b[106m"
            #define BG_DARK_PURPLE      "\x1b[45m"
            #define BG_ONYX             "\x1b[100m"
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
            #define LIGHT_BLUE          "\x1b[36m"
            #define ALMOND              "\x1b[37m"
            #define CRIMSON             "\x1b[31m"
            #define AQUA                "\x1b[36m"
            #define DARK_PURPLE         "\x1b[35m"
            #define ONYX                "\x1b[30m"

            #define BG_RED              "\x1b[41m"
            #define BG_BLUE             "\x1b[44m"
            #define BG_ORANGE           "\x1b[43m"
            #define BG_WHITE            "\x1b[47m"
            #define BG_HOT_PINK         "\x1b[45m"
            #define BG_GRAY             "\x1b[47m"
            #define BG_DARK_GRAY        "\x1b[47m"
            #define BG_PINK             "\x1b[45m"
            #define BG_GOLD             "\x1b[43m"
            #define BG_GREEN            "\x1b[42m"
            #define BG_PURPLE           "\x1b[45m"
            #define BG_DARK_GREEN       "\x1b[42m"
            #define BG_LAVENDER         "\x1b[46m"
            #define BG_YELLOW           "\x1b[43m"
            #define BG_TEAL             "\x1b[46m"
            #define BG_BROWN            "\x1b[43m"
            #define BG_BLACK            "\x1b[40m"
            #define BG_LIGHT_BLUE       "\x1b[46m"
            #define BG_ALMOND           "\x1b[47m"
            #define BG_CRIMSON          "\x1b[41m"
            #define BG_AQUA             "\x1b[46m"
            #define BG_DARK_PURPLE      "\x1b[45m"
            #define BG_ONYX             "\x1b[40m"
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
    #define LIGHT_BLUE          ""
    #define ALMOND              ""
    #define CRIMSON             ""
    #define AQUA                ""
    #define DARK_PURPLE         ""
    #define ONYX                ""

    #define BG_RED              ""
    #define BG_BLUE             ""
    #define BG_ORANGE           ""
    #define BG_WHITE            ""
    #define BG_HOT_PINK         ""
    #define BG_GRAY             ""
    #define BG_DARK_GRAY        ""
    #define BG_PINK             ""
    #define BG_GOLD             ""
    #define BG_GREEN            ""
    #define BG_PURPLE           ""
    #define BG_DARK_GREEN       ""
    #define BG_LAVENDER         ""
    #define BG_YELLOW           ""
    #define BG_TEAL             ""
    #define BG_BROWN            ""
    #define BG_BLACK            ""
    #define BG_LIGHT_BLUE       ""
    #define BG_ALMOND           ""
    #define BG_CRIMSON          ""
    #define BG_AQUA             ""
    #define BG_DARK_PURPLE      ""
    #define BG_ONYX             ""
#endif // __ENTITIES2_COLORS__

/** 
 * \def RESET
 * \brief If used, resets all colors and styling.<br>Format string: <code>{reset}</code>, <code>{end}</code> or <code>{blank}</code>
 * \hideinitializer
 */

/**
 * \def BOLD
 * \brief <b>Bold</b> text styling. <span style="background-color: rgb(0, 0, 0);"><b>\#\#\#TEST\#\#\#</b></span><br>Format string: <code>{bold}</code> or  <code>{b}</code>
 * \hideinitializer
 */

/**
 * \def FAINT
 * \brief Faint text styling.<br>Format string: <code>{faint}</code> or <code>{f}</code>
 * \warning Isn't supported by most terminals.
 * \hideinitializer
 */

/**
 * \def ITALIC
 * \brief <i>Italic</i> text styling. <span style="background-color: rgb(0, 0, 0);"><i>\#\#\#TEST\#\#\#</i></span>
          <br>Format string: <code>{italic}</code> or <code>{i}</code>
 * \hideinitializer
 */

/**
 * \def UNDERLINE
 * \brief <u>Underline</u> text styling. <span style="background-color: rgb(0, 0, 0);"><u>\#\#\#TEST\#\#\#</u></span>
          <br>Format string: <code>{underline}</code> or <code>{u}</code>
 * \hideinitializer
 */

/**
 * \def BLINKING
 * \brief Blinking text styling.
          <br>Format string: <code>{blinking}</code> or <code>{bli}</code>
 * \warning Isn't supported by most terminals.
 * \hideinitializer
 */

/**
 * \def RED
 * \brief RGB value = 255,25,0 <span style="background-color: rgb(0, 0, 0);color: rgb(255, 25, 0)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{red}</code>
 * \hideinitializer
 */

/**
 * \def BLUE
 * \brief RGB value = 36,80,255 <span style="background-color: rgb(0, 0, 0);color: rgb(36, 80, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{blue}</code>
 * \hideinitializer
 */

/**
 * \def ORANGE
 * \brief RGB value = 230,153,0 <span style="background-color: rgb(0, 0, 0);color: rgb(230, 153, 0)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{orange}</code>
 * \hideinitializer
 */

/**
 * \def WHITE
 * \brief RGB value = 230,230,230 <span style="background-color: rgb(0, 0, 0);color: rgb(230, 230, 230)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{white}</code>
 * \hideinitializer
 */

/**
 * \def HOT_PINK
 * \brief RGB value = 153,0,77 <span style="background-color: rgb(0, 0, 0);color: rgb(153, 0, 77)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{hot_pink}</code>
 * \hideinitializer
 */

/**
 * \def GRAY
 * \brief RGB value = 99,99,99 <span style="background-color: rgb(0, 0, 0);color: rgb(99, 99, 99)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{gray}</code>
 * \hideinitializer
 */

/**
 * \def DARK_GRAY
 * \brief RGB value = 68,68,68 <span style="background-color: rgb(0, 0, 0);color: rgb(68, 68, 68)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{dark_gray}</code>
 * \hideinitializer
 */

/**
 * \def PINK
 * \brief RGB value = 234,128,255 <span style="background-color: rgb(0, 0, 0);color: rgb(234, 128, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{pink}</code>
 * \hideinitializer
 */

/**
 * \def GOLD
 * \brief RGB value = 255,195,77 <span style="background-color: rgb(0, 0, 0);color: rgb(255, 195, 77)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{gold}</code>
 * \hideinitializer
 */

/**
 * \def GREEN
 * \brief RGB value = 0,255,42 <span style="background-color: rgb(0, 0, 0);color: rgb(0, 255, 42)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{green}</code>
 * \hideinitializer
 */

/**
 * \def PURPLE
 * \brief RGB value = 76,0,230 <span style="background-color: rgb(0, 0, 0);color: rgb(76, 0, 230)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{purple}</code>
 * \hideinitializer
 */

/**
 * \def DARK_GREEN
 * \brief RGB value = 181,196,27 <span style="background-color: rgb(0, 0, 0);color: rgb(181, 196, 27)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{dark_green}</code>
 * \hideinitializer
 */

/**
 * \def LAVENDER
 * \brief RGB value = 187,153,255 <span style="background-color: rgb(0, 0, 0);color: rgb(187, 153, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{lavender}</code>
 * \hideinitializer
 */

/**
 * \def YELLOW
 * \brief RGB value = 255,255,38 <span style="background-color: rgb(0, 0, 0);color: rgb(255, 255, 38)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{yellow}</code>
 * \hideinitializer
 */

/**
 * \def TEAL
 * \brief RGB value = 0,130,181 <span style="background-color: rgb(0, 0, 0);color: rgb(0, 130, 181)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{teal}</code>
 * \hideinitializer
 */

/**
 * \def BROWN
 * \brief RGB value = 153,77,0 <span style="background-color: rgb(0, 0, 0);color: rgb(153, 77, 0)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{brown}</code>
 * \hideinitializer
 */

/**
 * \def BLACK
 * \brief RGB value = 0,0,0 <span style="background-color: rgb(255, 255, 255);color: rgb(0, 0, 0)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{black}</code>
 * \hideinitializer
 */

/**
 * \def LIGHT_BLUE
 * \brief RGB value = 102,230,255 <span style="background-color: rgb(0, 0, 0);color: rgb(102, 230, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{light_blue}</code>
 * \hideinitializer
 */

/**
 * \def ALMOND
 * \brief RGB value = 255,238,204 <span style="background-color: rgb(0, 0, 0);color: rgb(255, 238, 204)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{almond}</code>
 * \hideinitializer
 */

/**
 * \def CRIMSON
 * \brief RGB value = 179,0,30 <span style="background-color: rgb(0, 0, 0);color: rgb(179, 0, 30)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{crimson}</code>
 * \hideinitializer
 */

/**
 * \def AQUA
 * \brief RGB value = 25,255,255 <span style="background-color: rgb(0, 0, 0);color: rgb(25, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{aqua}</code>
 * \hideinitializer
 */

/**
 * \def DARK_PURPLE
 * \brief RGB value = 38,0,77 <span style="background-color: rgb(255, 255, 255);color: rgb(38, 0, 77)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{dark_purple}</code>
 * \hideinitializer
 */

/**
 * \def ONYX
 * \brief RGB value = 23,22,22 <span style="background-color: rgb(255, 255, 255);color: rgb(23, 22, 22)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{onyx}</code>
 * \hideinitializer
 */

/**
 * \def BG_RED
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(255, 25, 25);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_red}</code>
 * \hideinitializer
 */

/**
 * \def BG_BLUE
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(36,80,255);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_blue}</code>
 * \hideinitializer
 */

/**
 * \def BG_ORANGE
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(230,153,0);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_orange}</code>
 * \hideinitializer
 */

/**
 * \def BG_WHITE
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(230, 230, 230);color: rgb(0, 0, 0)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_white}</code> or <code>{white_bg}</code>
 * \hideinitializer
 */

/**
 * \def BG_HOT_PINK
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(153,0,77);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_hot_pink}</code>
 * \hideinitializer
 */

/**
 * \def BG_GRAY
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(99,99,99);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_gray}</code>
 * \hideinitializer
 */

/**
 * \def BG_DARK_GRAY
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(68,68,68);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_dark_gray}</code>
 * \hideinitializer
 */

/**
 * \def BG_PINK
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(234,128,255);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_pink}</code>
 * \hideinitializer
 */

/**
 * \def BG_GOLD
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(255,195,77);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_gold}</code>
 * \hideinitializer
 */

/**
 * \def BG_GREEN
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(0,255,42);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_green}</code>
 * \hideinitializer
 */

/**
 * \def BG_PURPLE
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(76,0,230);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_purple}</code>
 * \hideinitializer
 */

/**
 * \def BG_DARK_GREEN
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(181,196,27);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_dark_green}</code>
 * \hideinitializer
 */

/**
 * \def BG_LAVENDER
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(187,153,255);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_lavender}</code>
 * \hideinitializer
 */

/**
 * \def BG_YELLOW
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(255,255,38);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_yellow}</code>
 * \hideinitializer
 */

/**
 * \def BG_TEAL
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(0,130,181);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_teal}</code>
 * \hideinitializer
 */

/**
 * \def BG_BROWN
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(153,77,0);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_brown}</code>
 * \hideinitializer
 */

/**
 * \def BG_BLACK
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(0,0,0);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_black}</code>
 * \hideinitializer
 */

/**
 * \def BG_LIGHT_BLUE
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(102,230,255);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_light_blue}</code>
 * \hideinitializer
 */

/**
 * \def BG_ALMOND
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(255,238,204);color: rgb(0, 0, 0)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_almond}</code>
 * \hideinitializer
 */

/**
 * \def BG_CRIMSON
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(179,0,30);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_crimson}</code>
 * \hideinitializer
 */

/**
 * \def BG_AQUA
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(255,238,204);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_aqua}</code>
 * \hideinitializer
 */

/**
 * \def BG_DARK_PURPLE
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(38,0,77);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_dark_purple}</code>
 * \hideinitializer
 */

/**
 * \def BG_ONYX
 * \brief Same RGB value as it's text color counterpart. <span style="background-color: rgb(23,22,22);color: rgb(255, 255, 255)">\#\#\#TEST\#\#\#</span>
          <br>Format string: <code>{bg_onyx}</code>
 * \hideinitializer
 */

// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0