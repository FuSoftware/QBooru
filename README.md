# QBooru

## Important notice
Since 1.15, a new version control relying on http://florentuguet.net16.net/ has been implemented. The software won't need to download the versions anymore.

## Summary
QBooru is a lightweight Windows, Linux and MacOS client that allows users to see pictures from most booru sites, and download them, for example :
<ul>
  <li>Gelbooru</li>
  <li>Danbooru</li>
  <li>Konachan</li>
  <li>Yandere</li>
  <li>Safebooru</li>
  <li>Rule34</li>
</ul>

At the moment, it supports 4 APIs :
<ul>
  <li>Gelbooru</li>
  <li>Danbooru 2</li>
  <li>Moebooru</li>
  <li>Derpibooru</li>
</ul>

Searchs are done by the JSON APIs. Thumbnails are cached locally, and are re-used by the program if needed.

## Interface
The current interface allows users to chose how many pictures they want, within 3-5 rows and 5-8 columns.
The recommended size is 3*5, as it fits perfectly the smallest window size.

Search tab example : http://puu.sh/cK0pj.jpg

## Configuration
Users can change nearly all the parameters through the Option tab, or by editing the configuration.json file.
Boorus can be added, edited, and deleted through the Booru tab in the software, but they can also be edited manually in the configuration file.

## Build instructions (Linux)
<ul>
  <li>Clone the git repo</li>
  <li>Install Qt and Qt creator</li>
  <ul>
    <li>Pacman : <code>sudo pacman -S qt5 qtcreator</code></li>
    <li>Yaourt : <code>yaourt -S qt5 qtcreator</code></li>
  </ul>
  <li>Load the .pro file in QtCreator (Qt >= 5)</li>
  <li>Put the now built executable in a folder with full R/W permissions</li>
  <li>Run it</li>
</ul>

## Build instructions (MacOS)
<ul>
  <li>Clone the git repo (Path shouldn't contain non-ASCII characters)</li>
  <li>Install XCode from App Store</li>
  <li>Install Qt</li>
  <ul>
    <li>MacPorts : <code>sudo port install qt5</code></li>
    <li>Homebrew : <code>brew install qt55</code> (Homebrew has bug with macdeployqt on Qt >= 5.6)</li>
    <li>Also you can install Qt from official site</li>
  </ul>
  <li>Make sure that qmake and macdeployqt is linked</li>
  <li>Cd into <code>builds</code> directory</li>
  <li>Run <code>qmake ../src/viewer/QBooru.pro && make && make clean</code></li>
  <li>Put the now built executable in a folder with full R/W permissions</li>
  <li>Run it</li>
</ul>

## Credits
cdunn2001 : https://github.com/open-source-parsers/jsoncpp for making the JSON parser JsonCPP
