@page DEMO_IMPLEMENTATION Demo Documentation
<p>This page explains how demos work, how the .edemo format works, and other stuff.<br>Table of contents:<br></p>
<ul>
    <li>
    <a href="#1">Demo System</a>
    <ul>
        <li>
        <a href="#1.1">What are demos?</a>
        </li>
        <li>
        <a href="#1.2">Possible Concerns</a>
        </li>
    </ul>
    </li>
    <li>
    <a href="#2">.edemo Format (v1.0.0)</a>
    <ul>
        <li>
        <a href="#2.1">Header</a>
        </li>
        <li>
        <a href="#2.2">Body</a>
        </li>
    </ul>
    </li>
</ul>

<a id="1"></a>
<h1>Demo System</h1>

<a id="1.1"></a>
<h2>What are demos?</h2>
<p>
A <b>demo</b> captures ingame gameplay like a normal video does, but not quite.<br>
A demo containts a sequence of <b>keypresses</b> that happened during the gameplay, and plays them back.<br>
This means that instead of sharing a huge video file, you can send this tiny demo file and other people<br>
can watch your gameplay natively in their own copy of entities2.<br><br>
In this document, you'll learn how it works in depth.
</p>

<a id="1.2"></a>
<h2>Possible Concerns</h2>
<p>
The main question here is:<br>
<b><i>Is there a possibility for desync?</i></b><br>
While it is possible, the .edemo format contains extra metadata for accurate playback.<br><br>
<b><i>Will old demos work in newer versions and vice versa?</i></b><br>
Yes! But only if the .edemo formats match. While the game itself cannot convert .edemo formats,<br>
there will be a standalone program that will be able to convert between ALL .edemo formats (assuming<br>there even will be that many of them).
</p>

<a id="2"></a>
<h1>.edemo Format (v1.0.0)</h1>

<a id="2.1"></a>
<h2>Header</h2>
<p>
The header contains some useful metadata about the demo.<br>
<table>
<tr>
    <th><b>Byte Width</b></th>
    <th><b>Offset From Start</b></th>
    <th><b>Type</b></th>
    <th><b>Description</b></th>
</tr>
<tr>
    <th>4</th>
    <th>0</th>
    <th>uint32</a></th>
    <th>Magic number identifier, that in ASCII form spells "EDEM".</th>
</tr>
</tr>
<tr>
    <th>4</th>
    <th>4</th>
    <th>uint32</a></th>
    <th>Game version.</th>
</tr>
<tr>
    <th>4</th>
    <th>8</th>
    <th>uint32</a></th>
    <th>.edemo format version.</th>
</tr>
<tr>
    <th>8</th>
    <th>12</th>
    <th>uint64</a></th>
    <th>The seed used for RNG.</th>
</tr>
<tr>
    <th>8</a></th>
    <th>20</th>
    <th>int64</th>
    <th>Unix timestamp of when the demo recording started.</th>
</tr>
<tr>
    <th>8</a></th>
    <th>28</th>
    <th>int64</th>
    <th>Unix timestamp of when the demo recording ended.</th>
</tr>
<tr>
    <th>4</th>
    <th>36</th>
    <th>uint32</th>
    <th>The length of the demo. (a.k.a. number of moves to read)</th>
</tr>
<tr>
    <th>1</th>
    <th>40</th>
    <th>uint8</th>
    <th>Difficulty of the game.</th>
</tr>
<tr>
    <th>#</th>
    <th>41</th>
    <th>string</th>
    <th>Username of the person that recorded the demo.<br>Null terminated.</th>
</tr>
</table>
</p>

<a id="2.2"></a>
<h2>Body</h2>
<p>
Rather than giving you a table, I will explain in text.<br>
The body of a demo, is essentially a sequence of bytes that are decoded by the game.<br><br>

Now, each move when written into the file is turned into an <b>int8</b> meaning the bytes are <b>signed</b>.<br>
Player moves have 4 bits from the right treated as the choice, and the resulting byte is <i>ALWAYS >=0</i>.<br>
Enemy moves work the same way, except they are <i>ALWAYS <0</i>.<br>
(In the code, if it's an enemy move, it's basically negated with the unary - operator.)<br><br>

For example, if the player picks move 2, it is stored as 2, however when the enemy picks the move 2<br>
it is stores as -2.<br><br>

Mentioned earlier is the unsigned 32 bit integer stating how many moves were recorded,<br>
so the game will read this many bytes and ignore the rest.
</p>