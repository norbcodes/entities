<h1>Compilation</h1>
<p>
To compile:
<pre><code>git clone https://github.com/norbcodes/entities
mkdir entities/enities2/build
cd entities/enities2/build
cmake ..
make
</code></pre>
You may also specify a custom generator. So if you're a MinGW user:
<pre><code>git clone https://github.com/norbcodes/entities
mkdir entities/enities2/build
cd entities/enities2/build
cmake .. -G "MinGW Makefiles"
mingw32-make
</code></pre>
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
        <th>DISABLE_COLORS</th>
        <th>OFF</th>
        <th>Disable colors and styling. ALL of it. WARNING: Will make your<br>game look ugly if disabled :)</th>
    </tr>
    <tr>
        <th>DISABLE_TERMINAL_BELL</th>
        <th>OFF</th>
        <th>Disable terminal bell.</th>
    </tr>
</table>