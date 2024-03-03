# MiniRT

**This projects aims to create a mini raytracer with basic features such as :**
* Ambient lighting 
* Spot lights
* Directionnal lights (bonus)
* Shadows
* Specular reflection (bonus)
* Reflection (bonus)
* Interactions (translation, resize, rotation) with objects and camera
* Interactions (translation, brightness) with lights
* Representation of basic objects (Speres, Cylinders, Planes)

Project finished at 110%.

---

**Here some snippets and a live demo :**

| ![Screenshot_2023-12-05_at_07.00.13](screenshots/Screenshot_2023-12-05_at_07-00-13.png) | ![Screenshot_2023-12-05_at_07.05.29](screenshots/Screenshot_2023-12-05_at_07-05-29.png) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![Screenshot_2024-03-03_at_21.13.16](screenshots/Screenshot_2024-03-03_at_21-13-16.png) | ![Screenshot_2024-03-03_at_21.14.12](screenshots/Screenshot_2024-03-03_at_21-14-12.png) |

https://github.com/Milvintsiss-42/miniRT/assets/38794405/a291a17e-f3b4-49ca-a0ef-669f58354d92

---

## Installation :

### Requirements : 
You need a minimal dev environnement (`gcc`, `make`, etc).

If you're on MacOS you also probably need to install `Xquartz`:
```console
brew install Xquartz
reboot
```

### Building and execution:
```console
git clone https://github.com/Milvintsiss-42/miniRT.git
cd miniRT
make bonus
./miniRT [some map file]
```
Maps files can be found in `maps` directory (most bonus files take 4-5 seconds to load, this raytracer is not optimized at all, be patient).

## Controls :

| KEY           | ACTION                                                       |
| ------------- | ------------------------------------------------------------ |
| Mouse click   | Selects the object or light pointed by mouse cursor.         |
| Mouse scroll  | Increments/Decrements the current parameter.                 |
| `C`           | Toggles camera interactions, when this flag is `ON` all interactions belongs to the camera. If the flag is `OF` interactions belongs to the selected objects/lights.<br />[Defaults to `ON`] |
| `S`, `T`, `R` | Switches between the following interaction modes:<br />`RESIZE (S):`<br />- Resizes the diameter of selected spheres.<br />- Resizes the diameter and/or height of selected cylinders.<br />- Increments/decrements intensity of selected lights.<br />- Zoom in/out (translates the camera in the direction pointed by the mouse cursor).<br />- Increments/decrements camera FOV.<br />`TRANSLATE (T):`<br />Translates the origin of the selected objects/lights/camera along the selected axis.<br />`ROTATE (R):`<br />Rotates the selected objects/camera along the selected axis.<br />[Defaults to `S`] |
| `X`, `Y`, `Z` | Selects the corresponding axis.<br />[Defaults to `X`]       |
| `L`           | Makes spot lights visible (represented by a small white sphere), you can only select lights when they are visible. |
| `SPACE`       | Unselects all objects and lights.                            |
| `M`           | Enables/disables reflection for all objects.                 |
| `F`           | Toggles FOV flag. When this flag is active, `RESIZE` action in camera mode will modify the camera FOV value, instead of triggering a zoom/dezoom.<br />[Defaults to `OF`] |
| `H`           | Toggles HEIGHT flag. When this flag is active, `RESIZE` action will modify the height of selected objects that have a height property.<br />This flag is additionable with DIAMETER flag.<br />[Defaults to `ON`] |
| `D`           | Toggles DIAMETER flag. When this flag is active, `RESIZE` action will modify the diameter of selected objects that have a diameter property.<br />This flag is additionable with HEIGHT flag.<br />This flag does not apply to spheres.<br />[Defaults to `OF`] |
| `A`           | Toggles AMB_LIGHT flag. When this flag is active, interactions will only apply to the ambiant light. So if a mouse scroll event occurs, it will increment/decrement the brightness of the ambiant light.<br />[Defaults to `OF`] |
