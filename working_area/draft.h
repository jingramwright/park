// Draft version to test algorithm and general functionality as a concept before writing code
// for the ESP8266.

int Calculate_Maximum_Bound_Distance_From_Sensor (int Maximum_Distance_From_Sensor, int Percentage_Boundary)
{
  int Maximum_Bound_Distance_From_Sensor = (Maximum_Distance_From_Sensor * Percentage_Boundary) / 100;
  
  return Maximum_Bound_Distance_From_Sensor;
}

int Calculate_Minimum_Bound_Distance_From_Sensor (int Maximum_Distance_From_Sensor, int Percentage_Boundary)
{
  int Minimum_Bound_Distance_From_Sensor = (Maximum_Distance_From_Sensor * (100 - Percentage_Boundary)) / 100;
  
  return Minimum_Bound_Distance_From_Sensor;
}

int Calculate_Percentage_Through_Range (int Minimum_Value, int Maximum_Value, int Current_Value)
{
  int Numerator   = Maximum_Value - Current_Value;
  int Denominator = Maximum_Value - Minimum_Value;
  
  int Percentage_Through_Range_Float = ((float)Numerator / (float)Denominator);
  int Percentage_Through_Range       = round(Percentage_Through_Range_Float * 100);
  
  return Percentage_Through_Range;
}

int Calculate_Number_Of_Leds_To_Show(int Percentage_Through_Range)
{
  float Percentage_Through_Range_Float = (float)Percentage_Through_Range / 100;
  
  int Number_Of_Leds_To_Show = ceil(Percentage_Through_Range_Float * (float)Total_Number_Of_Leds);
  
  return Number_Of_Leds_To_Show;
}


void Display_Distance(int Distance_To_Vehicle_From_Sensor, int Band_Maximum_Percentage, int Band_Minimum_Percentage)
{
  int Minimum_Bound_Distance_From_Sensor = int Calculate_Minimum_Bound_Distance_From_Sensor(Maximum_Distance_From_Sensor, Band_Minimum_Percentage);
  int Maximum_Bound_Distance_From_Sensor = int Calculate_Maximum_Bound_Distance_From_Sensor(Maximum_Distance_From_Sensor, Band_Maximum_Percentage);
  
  int Percentage_Through_Range = Calculate_Percentage_Through_Range(Minimum_Bound_Distance_From_Sensor,
                                                                    Maximum_Bound_Distance_From_Sensor,
                                                                    Distance_To_Vehicle_From_Sensor);
  
  int   Number_Of_Leds_To_Show  = Calculate_Number_Of_Leds_To_Show(Percentage_Through_Range);
  
  std::cout << "Lighting " << Number_Of_Leds_To_Show << " leds." << std::endl;
  
  // Clear Leds.
  
  for (int i = 0; i < Number_Of_Leds_To_Show; i++)
  {
    //leds[i] = CRGB::Blue; 
  }
}

void Calculate_Accuracy(int Distance_To_Vehicle_From_Sensor)
{
  int Percentage_Through_Range = Calculate_Percentage_Through_Range(Minimum_Distance_From_Sensor,
                                                                    Maximum_Distance_From_Sensor,
                                                                    Vehicle_Distance_From_Sensor);
      
  // Long Range - Low Accuracy.
  if (Percentage_Through_Range <= Long_Range_Percentage)
  {
    std::cout << "Long Range" << std::endl;
    Display_Distance(Distance_To_Vehicle_From_Sensor, 100, Long_Range_Percentage);
  }
  // Medium Range - Medium Accuracy.
  else if (Percentage_Through_Range <= Medium_Range_Percentage)
  {
    std::cout << "Medium Range" << std::endl;
    Display_Distance(Distance_To_Vehicle_From_Sensor, Long_Range_Percentage, Medium_Range_Percentage);
  }
  // Short Range - High Accuracy.
  else if (Percentage_Through_Range <= Short_Range_Percentage)
  {
    std::cout << "Short Range" << std::endl;
    Display_Distance(Distance_To_Vehicle_From_Sensor, Medium_Range_Percentage, Short_Range_Percentage);
  }
  // Issue occurred.
  else
  {
    // Error.
    std::cout << "Error" << std::endl;
  }
}

int main()
{
  // Vehicle is inside of the sensor's maximum distance.
  if (Vehicle_Distance_From_Sensor < Maximum_Distance_From_Sensor)
  {
    // Vehicle is closer than the sensor's minimum distance. 
    if (Vehicle_Distance_From_Sensor < Minimum_Distance_From_Sensor)
    {
      printf("Warning!");
    }
    // Vehicle distance progress can be displayed.
    else
    {
      Calculate_Accuracy(Distance_To_Vehicle_From_Sensor);
    }
  }
  
  return 0;
}