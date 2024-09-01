// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

// COLOR/STYLE MACROS
#ifdef __ENTITIES2_COLORS__
    #ifndef __ENTITIES2_4_BIT_COLORS__
        #define RESET               "\x1b[0m"
        #define BOLD                "\x1b[1m"
        #define FAINT               "\x1b[2m"
        #define ITALIC              "\x1b[3m"
        #define UNDERLINE           "\x1b[4m"
        #define BLINKING            "\x1b[5m"
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
#endif // __ENTITIES2_COLORS__