@page DATAPACK_DOC Datapack Documentation
<p>This page will explain how Datapacks work, and how you can make your own.</p>

<ul>
    <li>
    <a href="#1">What is a Datapack?</a>
    <ul>
        <li>
        <a href="#1.1">What type of file are they?</a>
        </li>
        <li>
        <a href="#1.2">How are they loaded in game?</a>
        </li>
    </ul>
    </li>
    <li>
    <a href="#2">Structure</a>
    <ul>
        <li>
        <a href="#2.1">"Datapack" block</a>
        </li>
        <li>
        <a href="#2.2">"Meta" block</a>
        </li>
        <li>
        <a href="#2.3">"Data" block</a>
        <ul>
            <li>
            <a href="#2.3.1">Exit Message block</a>
            </li>
            <li>
            <a href="#2.3.2">Greet block</a>
            </li>
            <li>
            <a href="#2.3.3">Translation block</a>
            </li>
        </ul>
        </li>
    </ul>
    </li>
</ul>

<a id="1"></a>
<h1>What is a Datapack?</h1>
<p>
A Datapack at its current state can add custom exit messages and custom greetings,<br>
as well as make custom translations or port the entire game to other languages!<br><br>
Sure, doesn't sound too exciting, but who doesn't love a bit of customization eh? ;)
</p>
<a id="1.1"></a>
<h2>What type of file are they?</h2>
<p>
Datapacks are <b>XML documents</b>. These files can be placed in the Datapack folder<br>
which is usually in the same folder as the exe itself. (You can change where the datapack folder<br>
is with the <code>-nd</code> command line argument).
</p>
<a id="1.2"></a>
<h2>How are they loaded in game?</h2>
<p>
Datapacks are only loaded once on startup. This means making a change to a Datapack<br>
requires you to exit from the game to apply the changes.<br>
Faulty Datapacks will also display an error in the Datapacks tab.
</p>

<a id="2"></a>
<h1>Structure</h1>
<p>A Datapack consists of 3 main blocks.</p>
<a id="2.1"></a>
<h2>"Datapack" block</h2>
<p>
The very first block that contains all of datapack info.<br>
Both "Meta" and "Data" blocks fall under this one.
</p>
<a id="2.2"></a>
<h2>"Meta" block</h2>
<p>
This block contains data about the Datapack. This block is absolutely required.<br>
It contains 4 necessary nodes:
<ul>
<li><b>Name</b> - Name of the Datapack.</li>
<li><b>Autor</b> - Who made the Datapack.</li>
<li><b>Description</b> - A small (or big) description of the Datapack.</li>
<li><b>DatapackId</b> - Special identifier.</li>
</ul>
If any of these are missing, the Datapack will not be loaded.<br><br>
This is how it looks like:<br>
<img src="meta_block.png" alt="Meta block"></img>
</p>
<a id="2.3"></a>
<h2>"Data" block</h2>
<p>
This is where the actual data in the Datapack is!
</p>

<a id="2.3.1"></a>
<h3>Exit Message block</h3>
<img src="exit_msg.png" alt="Exit msg example"></img>
<p>
This one, as seen there, adds a custom exit message!<br>
In the body, you can add your exit message, or you can add a translation key for localized<br>
strings.<br><br>
This is where the parameter <code>local_translation</code> comes in.<br>
If this is set to <code>"True"</code>, then it will only take translations from within the datapack itself,<br>
else it uses global translations.<br>
Parameter <code>formatting</code> states wheter the exit message should be formatted or not.<br>
If set to <code>"True"</code>, you can then use <code>{white}</code> or <code>{blue}</code> and other formatting tags.
</p>

<a id="2.3.2"></a>
<h3>Greet block</h3>
<img src="greet.png" alt="Greet example"></img>
<p>
This adds a custom greeting. Putting a translation string in the body works the same way as previously<br>
Both <code>formatting</code> and <code>local_translation</code> work the same as previously.<br>
Only new attribute is <code>time</code>. This specifies the time when the greeting can appear.<br>
Possible values are: Morning, Afternoon, Evening, EarlyNight, 3AM, All<br>
</p>

<a id="2.3.3"></a>
<h3>Translation block</h3>
<img src="translation.png" alt="Translation example"></img>
<p>
Now for the star of this show: translation blocks!!!<br>
In the body of this block, it's the string. Simple.<br><br>
<code>lang</code> attribute here is what language this belongs to.<br>
All language codes used by entities2 are <code>en-US</code>, <code>sk-SK</code>, <code>ru-RU</code>, <code>tl-PH</code> and <code>pt-PT</code>.<br>The first two letters are set by ISO 639 norm, and the last two are set by ISO 3166-2 norm.<br><br>
<code>id</code> attribute here is the translation key, like <code>menu.main.subtitle</code> or <code>general.on</code> for example.<br><br>
<code>overwrite</code>, if set to True, means that the translation is overwritting global translations. If set to False,
<br>it will not affect translations and will be local to the Datapack.
</p>