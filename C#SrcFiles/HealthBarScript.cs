using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HealthBarScript : MonoBehaviour
{
    public Slider slider;
    public Gradient gradient;
    public Image fill;

    public void SetMaxHealth(int points)
    {
        slider.maxValue = points;
        slider.value = points;
        fill.color = gradient.Evaluate(1f);
    }

    public void SetHealth(int points)
    {
        slider.value = points;
        fill.color  = gradient.Evaluate(slider.normalizedValue);
    }

}
