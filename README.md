# QBooru

##Important notice
Since 1.9, Gelbooru XML is depreciated, the JSON one is now used. Please apply the following changes to your Gelbooru sites' configuration :
<ul>
  <li>Change in your Gelbooru based website settings the search_file extensions from XML to JSON</li>
  <li>Add to the search_url in your Gelbooru based website settings the term "&json=1"</li>
  <li>or</li>
  <li>Refer to "search_file_path" and "search_url" in https://github.com/FlorentUguet/QBooru/releases/download/v1.9.0/configuration.json</li>
</ul>

##Summit
QBooru is a lightweight Windows and Linux client that allows users to see pictures from most booru sites, and download them, for example :
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

##Interface
The current interface allows users to chose how many pictures they want, within 3-5 rows and 5-8 columns.
The recommended size is 3*5, as it fits perfectly the smallest window size.

Search tab example : http://puu.sh/cK0pj.jpg

##Configuration
Users can change nearly all the parameters through the Option tab, or by editing the configuration.json file.
Boorus can be added, edited, and deleted through the Booru tab in the software, but they can also be edited manually in the configuration file.

##Credits
cdunn2001 : https://github.com/open-source-parsers/jsoncpp for making the JSON parser JsonCPP

leethomason : https://github.com/leethomason/tinyxml2 for making the XML parser TinyXML2
