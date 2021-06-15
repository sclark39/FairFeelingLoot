# Fair Feeling Loot
## YOU MUST BUY THIS PLUGIN FROM THE UNREAL MARKETPLACE TO USE IT.
This github repository is provided for reference purposes ONLY and to make maintenance and support easier for those with a license to the plugin. Feel free to submit issues and fixes / improvements as pull requests.

To receive a license to the software you must purchase it from the Unreal Marketplace:
- https://www.unrealengine.com/marketplace/en-US/product/fair-feeling-loot

### Marketplace Description

When your player kills a monster, what loot should you drop? How will you randomize it? This plugin provides a graph-based editor for creating Loot Table Definitions describing how your random drop logic should work, as well as what randomly rolled stats your loot should have. You can use this to craft a fun looting experience for your players.

Within your Loot Table Definition you can use multiple forms of random choice, including weighted choice, shuffle-bag, and negentropy. Loot Table Definitions also allow for dynamic weights, and offer parameters that can be used to drive logic and decisions within the Loot Table Definition’s graph. By utilizing different forms of random choice and smart usage of parameters, you can craft an experience for your players that feels random, but also feels fair.

Features:
* New Asset Type: Loot Table Definition (Graph based loot table)
* New Actor Interface: Loot Source Interface (Add to your monster or treasure box actors so that they may specify which Loot Table Definition should be used)
* New Actor Component: Loot Generation Component (holds loot generation state and uses Loot Table Definitions or actors implementing the Loot Source Interface to generate Loot Recipes)
* Live Updating -- edit your Loot Table Definitions in real-time while running your game
* Multiple types of random choice (Weighted Random, Shuffle-bag, Negentropy)
* Multiple types of flow control within the Loot Table Definition (Sequence, Repeat, Test Parameter, Switch on Parameter)
* Uses Gameplay Tags for Loot Type, Loot Tags, and Loot Stats
* Nested Loot Table Definitions can be used to split up and reuse your Loot Table Definitions, to make it easier to maintain and organize them across a large game
* Loot generation state is tracked uniquely per Loot Generation Component, which allows this system to be utilized in a singleplayer or multiplayer setting.

