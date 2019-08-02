# UE4-Menu-System
A project only focused on Widget and UI functionality. (E.g. Main Menu, In game menu)

<p>The idea behind this repo / project is to seperate the menu logic and have a standard template that I can easily implement for prototyping and such. This Read Me is meant to help me more so than others to find my way around again.</p>

# Usage
Because UE4 is a bit lame in regards of using additional projects within the solution (e.g. upon re-generating visual studio files it'll simply delete the (previously) added project from the solution) and how the assets would essentially have to be migrated too, the way to approach it is the following, scroll down to the bottom for C++:

https://wiki.unrealengine.com/Migrate_content_between_projects

Also add "UMG" to the dependency's in Build.cs for the menu system to work.
