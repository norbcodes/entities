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
You may also add options, after the `..`.<br>
This will produce an executable named <code>entities2.exe</code> (or <code>entities2.out</code> or something similar)<br>
To run, simply run the executable as you would any other:
<pre><code>./entities2.exe</code></pre>
Or similar.<br><br>
<b>Precompiled binaries are not provided.</b>
</p>