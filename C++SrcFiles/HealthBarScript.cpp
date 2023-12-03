#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class HealthBarScript : public MonoBehaviour
{
private:
    Slider* slider;
    Gradient* gradient;
    Image* fill;

public:
    void SetMaxHealth(int points) {
        slider->maxValue = points;
        slider->value = points;
        fill->color = gradient->Evaluate(1.0f);
    }

    void SetHealth(int points) {
        slider->value = points;
        fill->color = gradient->Evaluate(slider->normalizedValue);
    }
};
