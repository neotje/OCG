[![OCG build](https://github.com/neotje/OCG/actions/workflows/main.yml/badge.svg)](https://github.com/neotje/OCG/actions/workflows/main.yml)

# OCG

Open Car Glow

# Adding an effect

1. Create an effect class in the 'lib/effects' folder.

```c++
class MyEffect : public Effect {
    public:
        MyEffect() : Effect("Effect Menu name") { }
};
```

2. Add the effect to 'effects' list in 'lib/effects/effects.h'.

```c++
void effectsSetup() {
    ...
    effects.add(new MyEffect());
    ...
}
```

3. Add persistant config variables to 'include/types.h'.

```c++
struct MyEffectConfig {
    // Variables
};

struct Config {
    // ...
    MyEffectConfig myEffect;
};
```

4. Set default values to 'include/config.h'

```c++
Config config = {
    // ...
    .myEffect = {
        // ...
    }
};

bool resetConfig() {
    config = {
        // ...
        .myEffect = {
            // ...
        }
    };
    
    // ...
}
```

5. Add config screen to the menu state machine.

```c++
class MainMenuState : public MenuScreen {
    public:
        MainMenuState() { }
        ~MainMenuState() { }

        int onClick(int entryIndex) {
            if (entryIndex == 2) {
                switch (getConfig()->currentEffect) {
                    case /* myEffect index */:
                        return myEffectConfigScreen.index;

            }

            return -1;
        }
};
```
