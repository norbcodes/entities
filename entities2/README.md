<h1>Compilation</h1>
<p>
<b>REMEMBER, DO NOT DOWNLOAD FROM "RELEASES" SECTION. GIT CLONE THIS REPO.</b><br>
To compile:
<pre><code>git clone https://github.com/norbcodes/entities.git
cd entities/entities2
mkdir build
cd build
cmake ..
make
</code></pre>
<b>If you wish to test a dev build, you need to explicitly use <code>--branch</code> parameter when cloning!</b><br>
You may also specify a custom generator. So if you're a MinGW user:
<pre><code>git clone https://github.com/norbcodes/entities.git
cd entities/entities2
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
</code></pre>
CMake supports many build systems, read the docs to learn how to adjust it to your build system.<br>
You may also add options, after the <code>..</code> <a href="#options">See options here</a>.<br>
This will produce an executable named <code>entities2.exe</code> (or <code>entities2.out</code> or something similar)
<br>
Then, simply run the executable as you would any other:
<pre><code>./entities2.exe</code></pre>
Or similar.<br><br>
<b>Precompiled binaries are not provided.</b>
</p>

<a id="options"></a>
<h2>CMake Options</h2>
<p>To use these, do so as: -D<code>{option}</code>=ON<br>
<b>Remember, these are COMPILE options. If you want to enable one of these, you must recompile the whole game.</b>
</p>
<table>
    <tr>
        <th>Option</th>
        <th>Default</th>
        <th>Info</th>
    </tr>
    <tr>
        <th>STATIC_LIBS</th>
        <th>OFF</th>
        <th>Statically link against C and C++ standard lib.<br>Expect an increase in filesize when using this option!</th>
    </tr>
    <tr>
        <th>OPTIMIZE</th>
        <th>OFF</th>
        <th>Enable optimization. When used, the following<br>options are passed to the compiler:<br><b>-O2</b> (Optimization level 2)<br><b>-g0</b> (No debug info)<br><b>-ggdb0</b> (No debug info)<br><b>-s</b> (Strip symbol table)</th>
    </tr>
    <tr>
        <th>ENABLE_DISCORD_RPC</th>
        <th>OFF</th>
        <th>Enable Discord RPC. If you want to use it later,<br>you must recompile with this option present.<br><br>If not present, doesn't build the discord-rpc library either.</th>
    </tr>
    <tr>
        <th>CUSTOM_DISCORD_ID</th>
        <th>OFF</th>
        <th>Custom Discord ID. If set to OFF, the game will use the<br> original client id. To pass in a custom client id, just pass it into<br> this option, like <code>-DCUSTOM_DISCORD_ID="42069"</code></th>
    </tr>
    <tr>
        <th>BUILD_DOCS</th>
        <th>OFF</th>
        <th>Enable building of Doxygen documentation.</th>
    </tr>
    <tr>
        <th>DISABLE_COLORS</th>
        <th>OFF</th>
        <th>Disable colors and styling. ALL of it. WARNING: Will make your<br>game look ugly if enabled :)</th>
    </tr>
    <tr>
        <th>4BIT_COLORS</th>
        <th>OFF</th>
        <th>Use 4bit colors instead of RGB (ONLY WORKS WHEN COLORS ENABLED)<br>This will make the game use the predefined terminal colors, that should be more<br>widely supported than full RGB colors.</th>
    </tr>
    <tr>
        <th>4BIT_STYLES</th>
        <th>OFF</th>
        <th>Enable styling when in 4Bit color mode (ONLY WORKS WHEN 4BIT COLORS ENABLED)<br>Yknow, things like bold, italic, underline...</th>
    </tr>
    <tr>
        <th>4BIT_AIXTERM</th>
        <th>OFF</th>
        <th>Enable bright colors basically (ONLY WORKS WHEN 4BIT COLORS ENABLED)</th>
    </tr>
    <tr>
        <th>DISABLE_TERMINAL_BELL</th>
        <th>OFF</th>
        <th>Disable terminal bell.</th>
    </tr>
    <tr>
        <th>DISABLE_UNSTABLE_WARN</th>
        <th>OFF</th>
        <th>Use this if you don't want a warning when you build a dev version of this game.</th>
    </tr>
    <tr>
        <th>BUILT_IN_RUSSIAN</th>
        <th>OFF</th>
        <th>Embed all of Russian translation into the game. Will increase file size!</th>
    </tr>
    <tr>
        <th>BUILT_IN_SLOVAK</th>
        <th>OFF</th>
        <th>Embed all of Slovak translation into the game. Will increase file size!</th>
    </tr>
    <tr>
        <th>BUILT_IN_TAGALOG</th>
        <th>OFF</th>
        <th>Embed all of Tagalog translation into the game. Will increase file size!</th>
    </tr>
    <tr>
        <th>BUILT_IN_PORTUGUESE</th>
        <th>OFF</th>
        <th>Embed all of Portuguese translation into the game. Will increase file size!</th>
    </tr>
    <tr>
        <th>OLD_BEHAVIOR</th>
        <th>OFF</th>
        <th>When a translation key doesn't exist, print it out instead of searching in English translations</th>
    </tr>
</table>
