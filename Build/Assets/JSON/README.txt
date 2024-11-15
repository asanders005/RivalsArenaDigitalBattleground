REMEMBER: replace spaces in ALL file names with underscores
so that they can be read properly!
All images should be formatted as .pngs
Each deck image folder contains a cardback.png and a herocardback.png

/--------------------------------------------------/

JSON files follow this structure:
Deck:
    Starter string array
    Tier1 string array
    Tier2 string array
    Hero string array
Starter:
    Starter card component array
Tier1:
    Tier1 card component array
Tier2:
    Tier2 card component array
Hero:
    Hero card component array
	
/--------------------------------------------------/

Card ability components are stored in arrays, and while
typically they evaluate to an int (the amount they damage,
shield, etc.), sometimes, like in the case of triggered or
conditional abilities, they will evaluate to the card ability
component that they result in.