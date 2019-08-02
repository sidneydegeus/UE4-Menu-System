# UE4-Menu-System
A project (Currently barebones) only focused on Widget and UI functionality. (E.g. Main Menu, In game menu)

<p>The idea behind this repo / project is that it's a very clean project with one focus and that it can be seperately added to new projects relatively easily. The less code there is the easier it is for me to come back to it and/or to add stuff that were added in seperate projects to have a better menu system template for next time.</p>

<p>The entire read me is completely aimed towards myself so that I can remind myself, but if anyone finds it and wants to use it, enjoy. 

# Usage
1. Create a GameInstance C++ class that inherits from the MenuSystemGameInstance. (OR simply use the original MenuSystemGameInstance)
2. Create a GameInstance blueprint that inherits from your new GameInstance C++ (Or MenuSystemGameInstance)
3. Set default GameInstance to the in project settings to the created blueprint. (The blueprint servers to easily change string references without having to recompile etc.)
4. OPTIONAL: Open MainMenuLevel blueprint and change the cast to GameInstance from MenuSystemGameInstance to your GameInstance. (NOT THE BLUEPRINT, try to avoid any logic in the GameInstance blueprint. As I said, it's meant to easily fix stuff such as string references to maps and what not without having to recompile)

# Setup
Because UE4 is a bit lame in regards of using additional projects within the solution (e.g. upon re-generating visual studio files it'll simply delete the (previously) added project from the solution) and how the assets would essentially have to be migrated too:

Steps to get it working flawlessly:

1. Copy Source code (MenuSystem folder) to new project. e.g. Source/newproject/MenuSystem 
2. Delete MenuSystemGameModeBase.cpp/.h, MenuSystem.cpp/.h and MenuSystem.Build.cs
3. Generate Visual Studio files (right click uproject file)
4. Autoreplace in whole project MENUSYSTEM_API to NEWPROJECTNAME_API
5. Add "UMG" to the dependency's in the new project's Build.cs.
6. Add Redirects to DefaultEngine.ini and change newname with given projectname:

[CoreRedirects]
+ClassRedirects=(MatchSubstring=True,OldName="/MenuSystem",NewName="/NewProjectName")
+EnumRedirects=(MatchSubstring=True,OldName="/MenuSystem",NewName="/NewProjectName")
+FunctionRedirects=(MatchSubstring=True,OldName="/MenuSystem",NewName="/NewProjectName")
+StructRedirects=(MatchSubstring=True,OldName="/MenuSystem",NewName="/NewProjectName")

7. If UnrealEditor with new project is open, close and re-open so that the .ini changes can take effect.
8. Open MenuSystem project and use the Migrate tool in UE4 for the MenuSystem folder so that the assets / blueprints get migrated to the new project.
9. Open a MenuSystem blueprint in the new project to see if it opens succesfully. If so, congrats. If not, delete MenuSystem content from new project and repeat from step 7.

Finally, after the newly migrated assets and maps are opened in the new project, there may be errors/warnings for the copied C++ classes. A resave of those assets will clear those errors.

Original source:
https://wiki.unrealengine.com/Migrate_content_between_projects





