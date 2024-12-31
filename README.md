<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This Third-Person Shooter game was built to be an extendable prototype with a sandbox and prototype level. The game contains different weapon types, ammo types, explosive objects, Enemy AI, and animations. I built this using a combination of C++ and Blueprints. Players have an inventory system, item pickups, varying footstep audio and visual for different material types, and health pickup. The prototype is easily extendable and modifiable for different character and enemy meshes.

## Game Mechanics

The game focuses on gun play and movement. Players can pickup different weapons, ammo, and health items.

* Movement and shooting: Players can use WASD to move, space bar to jump, and 'ctrl' key to crouch. Right-click to zoom and left-click to shoot. Players have an inventory which holds upto 5 guns which can be selected and replaced with new pickups using the 'E' key.
* Enemies: Enemies use behaviour trees for their actions. Enemies patrol between two set patrol points. Enemies can agro the player if they are damaged by them or enter their range.
* Explosives: Explosive barrels can be damaged by the players and apply damage to any surrounding enemies. Enemies damaged by the explosion will agro the player based on their behaviour tree.


### Built With

* Unreal Engine 5.3

### Prerequisites

* Windows 10+
* Unreal Engine 5.3


### Installation

1. Clone the repo
2. Open Project in Unreal Engine
3. Play the Project inside Unreal Engine or Make a Build
4. Enjoy!

<!-- CONTACT -->
## Contact

* Siddharth Singhai - sidsinghai97@gmail.com
* [![LinkedIn][linkedin-shield]][linkedin-url]
* [![Portfolio][portfolioIcon-url]][portfolio-url]

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[portfolioIcon-url]: https://img.shields.io/badge/-Portfolio-brightgreen
[linkedin-url]: https://www.linkedin.com/in/siddharthsinghai97/
[portfolio-url]: https://sidsinghai97.wixsite.com/portfolio
