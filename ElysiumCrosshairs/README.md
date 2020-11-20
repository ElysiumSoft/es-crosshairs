# ESoft Crosshairs
> Simple app to draw a crosshair in any game window

## Configuration
Configuration is (for now) done in the `Main.cpp` file.
Simply edit the `InitializeGlobals` function as follows:

---

```cpp
VOID InitializeGlobals()
{
	//	TARGET WINDOW NAME
	g_title = L"ChangeMe";	// Change "ChangeMe" to the title of the target window, ie "FiveM"

	//	CROSSHAIR COLOUR
	g_red = 255;  //  Red component of crosshair colour
	g_green = 0;  //  Green component of crosshair colour
	g_blue = 0;   //  Blue component of crosshair colour

	//	CROSSHAIR SIZE AND THICKNESS
	g_thickness = 1;		      // Fiddle with
	g_crosshair_width = 36;	  // These Values
	g_crosshair_height = 36;  // Until Happy

	//	DEFINES COLOUR TO KEY OUT FOR TRANSPARENCY
	g_hbrColourKey = CreateSolidBrush(RGB(255, 0, 255)); // You don't need to change this unless you want your crosshair this colour, then change it to anything different to the crosshair colour
}
```
> This will be moved to a configuration file in future!

---

## Building
> This project was created with Visual Studio 2019, compatiblity with previous versions cannot be guaranteed.

#### 🔵 Clone the project from github:
```bash
git clone https://github.com/ElysiumSoft/es-crosshairs
```

#### 🔵 Open `ElysiumCrosshairs.vcxproj` in VS2019, it can be found in the root directory of the newly cloned repository.

#### 🔵 Edit the variables in the `IntializeGlobals` function to meet your requirements.

#### 🔵 Finally, build the project using Build->Build Solution or F5. And then run the built app


---

## Usage

#### Simply run the application and it will draw onto the window with the title specified in the `InitializeGlobals` function. To exit press `F4`

---