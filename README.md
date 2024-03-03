# MiniRT






| ![Screenshot_2023-12-05_at_07.00.13](screenshots/Screenshot_2023-12-05_at_07-00-13.png) | ![Screenshot_2023-12-05_at_07.05.29](screenshots/Screenshot_2023-12-05_at_07-05-29.png) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![Screenshot_2024-03-03_at_21.13.16](screenshots/Screenshot_2024-03-03_at_21-13-16.png) | ![Screenshot_2024-03-03_at_21.14.12](screenshots/Screenshot_2024-03-03_at_21-14-12.png) |

### Controls

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

