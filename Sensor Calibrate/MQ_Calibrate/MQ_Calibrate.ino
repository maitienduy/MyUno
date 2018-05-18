#define         MQ_135                       (1) //define which analog input channel you are going to use
#define         MQ_136                       (2)
#define         MQ_131                       (3)
#define         MQ_137                       (4)
#define         MQ_7                         (5)
#define         RL_VALUE_135                     (20) //define the load resistance on the board, in kilo ohms
#define         RL_VALUE_136                     (5)
#define         RL_VALUE_131                     (5)
#define         RL_VALUE_137                     (47)
#define         RL_VALUE_7                       (10)
#define         RO_CLEAN_AIR_FACTOR_135         (3.65) //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
#define         RO_CLEAN_AIR_FACTOR_136         (17.12)
#define         RO_CLEAN_AIR_FACTOR_131         (17.13)
#define         RO_CLEAN_AIR_FACTOR_137         (3.558)
#define         RO_CLEAN_AIR_FACTOR_7           (26.29)
/**************************************************************************************/
#define         CALIBARAION_SAMPLE_TIMES     (3)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (1000)   //define the time interal(in milisecond) between each samples in the
/*****************************Point Data***********************************************/
float           MQ135P1[2]  =  {10, 2.3};
float           MQ135P2[2]  =  {200, 0.8};
float           MQ136P1[2]  =  {5, 6};
float           MQ136P2[2]  =  {100, 0.54};
float           MQ131P1[2]  =  {5, 6};
float           MQ131P2[2]  =  {100, 0.54};
float           MQ137P1_CO[2]  =  {10, 2.853};
float           MQ137P2_CO[2]  =  {100, 1.64};
float           MQ137P1_NH3[2]  =  {10, 1.543};
float           MQ137P2_NH3[2]  =  {200, 0.6};
float           MQ7P1[2]  =  {100, 1};
float           MQ7P2[2]  =  {4000, 0.09};
/**********************************MQ 135 variable**********************************************/
float Ro_MQ135;
float ppm_MQ135 = 450;
float rs_ro_ratio_MQ135;
float Rs_MQ135;
float a_MQ135;
float b_MQ135;
/**********************************MQ 136 variable**********************************************/
float ppm_MQ136 = 0.034;
float rs_ro_ratio_MQ136;
float Rs_MQ136;
float Ro_MQ136;
float a_MQ136;
float b_MQ136;
/**********************************MQ 131 variable**********************************************/
float ppm_MQ131 = 0.059;
float rs_ro_ratio_MQ131;
float Rs_MQ131;
float Ro_MQ131;
float a_MQ131;
float b_MQ131;
/**********************************MQ 137 CO variable**********************************************/
float ppm_MQ137_CO = 4.4;
float rs_ro_ratio_MQ137_CO;
float Rs_MQ137_CO;
float Ro_MQ137_CO;
float a_MQ137_CO;
float b_MQ137_CO;
/**********************************MQ 137 NH3 variable**********************************************/
float ppm_MQ137_NH3 = 25;
float rs_ro_ratio_MQ137_NH3;
float Rs_MQ137_NH3;
float Ro_MQ137_NH3;
float a_MQ137_NH3;
float b_MQ137_NH3;
/**********************************MQ 7 variable**********************************************/
float ppm_MQ7 = 4.4;
float rs_ro_ratio_MQ7;
float Rs_MQ7;
float Ro_MQ7;
float a_MQ7;
float b_MQ7;
/**********************************Global variable**********************************************/
float ppm;

void setup()
{ Serial.begin(9600);
  Serial.println("Calculating...");
  /****************************************MQ135 setup*****************************************/
  Rs_MQ135 = GetRs(MQ_135, RL_VALUE_135, RO_CLEAN_AIR_FACTOR_135); // MQ135
  b_MQ135 = Getb(MQ135P1, MQ135P2, b_MQ135);
  a_MQ135 = Geta(MQ135P1, a_MQ135, b_MQ135);
  Ro_MQ135 = GetRo(MQ135P1, MQ135P2, ppm_MQ135, Rs_MQ135, a_MQ135, b_MQ135);
  /****************************************MQ136 setup*****************************************/
  Rs_MQ136 = GetRs(MQ_136, RL_VALUE_136, RO_CLEAN_AIR_FACTOR_136); // MQ136
  b_MQ136 = Getb(MQ136P1, MQ136P2, b_MQ136);
  a_MQ136 = Geta(MQ136P1, a_MQ136, b_MQ136);
  Ro_MQ136 = GetRo(MQ136P1, MQ136P2, ppm_MQ136, Rs_MQ136, a_MQ136, b_MQ136);
  /****************************************MQ131 setup*****************************************/
  Rs_MQ131 = GetRs(MQ_131, RL_VALUE_131, RO_CLEAN_AIR_FACTOR_131); // MQ131
  b_MQ131 = Getb(MQ131P1, MQ131P2, b_MQ131);
  a_MQ131 = Geta(MQ131P1, a_MQ131, b_MQ131);
  Ro_MQ131 = GetRo(MQ131P1, MQ131P2, ppm_MQ131, Rs_MQ131, a_MQ131, b_MQ131);
  /****************************************MQ137 CO setup*****************************************/
  Rs_MQ137_CO = GetRs(MQ_137, RL_VALUE_137, RO_CLEAN_AIR_FACTOR_137); // MQ137 CO
  b_MQ137_CO = Getb(MQ137P1_CO, MQ137P2_CO, b_MQ137_CO);
  a_MQ137_CO = Geta(MQ137P1_CO, a_MQ137_CO, b_MQ137_CO);
  Ro_MQ137_CO = GetRo(MQ137P1_CO, MQ137P2_CO, ppm_MQ137_CO, Rs_MQ137_CO, a_MQ137_CO, b_MQ137_CO);
  /****************************************MQ137 NH3 setup*****************************************/
  Rs_MQ137_NH3 = GetRs(MQ_137, RL_VALUE_137, RO_CLEAN_AIR_FACTOR_137); // MQ137 NH3
  b_MQ137_NH3 = Getb(MQ137P1_NH3, MQ137P2_NH3, b_MQ137_NH3);
  a_MQ137_NH3 = Geta(MQ137P1_NH3, a_MQ137_NH3, b_MQ137_NH3);
  Ro_MQ137_NH3 = GetRo(MQ137P1_NH3, MQ137P2_NH3, ppm_MQ137_NH3, Rs_MQ137_NH3, a_MQ137_NH3, b_MQ137_NH3);
  /****************************************MQ7 setup*****************************************/
  Rs_MQ7 = GetRs(MQ_7, RL_VALUE_7, RO_CLEAN_AIR_FACTOR_7); // MQ7
  b_MQ7 = Getb(MQ7P1, MQ7P2, b_MQ7); 
  a_MQ7 = Geta(MQ7P1, a_MQ7, b_MQ7); 
  Ro_MQ7 = GetRo(MQ7P1, MQ7P2, ppm_MQ7, Rs_MQ7, a_MQ7, b_MQ7);
  /******************************************************************************************/
  Serial.println("Setup Done!");
}

void loop()
{ Serial.println("AQM Detail:");
  /***********************************MQ135 main*********************************************
  Rs_MQ135 = MQCalibration(MQ_135, RL_VALUE_135, RO_CLEAN_AIR_FACTOR_135);
  rs_ro_ratio_MQ135 = Rs_MQ135 / Ro_MQ135;
  Serial.print("CO2: ");
  ppm = Getppm(rs_ro_ratio_MQ135, a_MQ135, b_MQ135);
  Serial.print(ppm, 4);
  Serial.println("ppm" );
  /************************************MQ136 main********************************************
  Rs_MQ136 = MQCalibration(MQ_136, RL_VALUE_136, RO_CLEAN_AIR_FACTOR_136);
  rs_ro_ratio_MQ136 = Rs_MQ136 / Ro_MQ136;
  Serial.print("SO2: ");
  ppm = Getppm(rs_ro_ratio_MQ136, a_MQ136, b_MQ136);
  Serial.print(ppm, 4);
  Serial.println("ppm" );
  /************************************MQ131 main********************************************
  Rs_MQ131 = MQCalibration(MQ_131, RL_VALUE_131, RO_CLEAN_AIR_FACTOR_131);
  rs_ro_ratio_MQ131 = Rs_MQ131 / Ro_MQ131;
  Serial.print("O3: ");
  ppm = Getppm(rs_ro_ratio_MQ131, a_MQ131, b_MQ131);
  Serial.print(ppm, 4);
  Serial.println("ppm" );
  /************************************MQ137 CO main********************************************/
  Rs_MQ137_CO = MQCalibration(MQ_137, RL_VALUE_137, RO_CLEAN_AIR_FACTOR_137);
  rs_ro_ratio_MQ137_CO = Rs_MQ137_CO / Ro_MQ137_CO;
  Serial.print("MQ137 CO: ");
  ppm = Getppm(rs_ro_ratio_MQ137_CO, a_MQ137_CO, b_MQ137_CO);
  Serial.print(ppm, 4);
  Serial.println("ppm" );
  /************************************MQ137 NH3 main********************************************
  Rs_MQ137_NH3 = MQCalibration(MQ_137, RL_VALUE_137, RO_CLEAN_AIR_FACTOR_137);
  rs_ro_ratio_MQ137_NH3 = Rs_MQ137_NH3 / Ro_MQ137_NH3;
  Serial.print("NH3: ");
  ppm = Getppm(rs_ro_ratio_MQ137_NH3, a_MQ137_NH3, b_MQ137_NH3);
  Serial.print(ppm, 4);
  Serial.println("ppm" );
  /************************************MQ7 main********************************************/
  Rs_MQ7 = MQCalibration(MQ_7, RL_VALUE_7, RO_CLEAN_AIR_FACTOR_7);
  rs_ro_ratio_MQ7 = Rs_MQ7 / Ro_MQ7;
  Serial.print("MQ7 CO: ");
  ppm = Getppm(rs_ro_ratio_MQ7, a_MQ7, b_MQ7);
  Serial.print(ppm, 4);
  Serial.println("ppm" );
  /******************************************************************************************/
  Serial.println("\n");
  delay(1000);
}

/************************************************************************************/
/*******************CALCULATE ELEMENT************************************************/
/****************** MQResistanceCalculation *****************************************/
float MQResistanceCalculation(float RL_VALUE, int raw_adc, float RO_CLEAN_AIR_FACTOR)
{
  return ( ((float)RL_VALUE * (1023 - raw_adc) / raw_adc));
}
/***************************** MQCalibration ****************************************/
float MQCalibration(int mq_pin, float RL_VALUE, float RO_CLEAN_AIR_FACTOR)
{
  int i;
  float val = 0;

  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {      //take multiple samples
    val += MQResistanceCalculation(RL_VALUE, analogRead(mq_pin), RO_CLEAN_AIR_FACTOR);
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val / CALIBARAION_SAMPLE_TIMES;                 //calculate the average value

  val = val / RO_CLEAN_AIR_FACTOR; //divided by RO_CLEAN_AIR_FACTOR yields the Ro
  //according to the chart in the datasheet
  return val;
}
/**************************************************************************************/
float GetRs(int mq_pin, float RL_VALUE, float RO_CLEAN_AIR_FACTOR)
{
  int i;
  float val = 0;

  for (i = 0; i < 10; i++) {      //take multiple samples
    val += MQResistanceCalculation(RL_VALUE, analogRead(mq_pin), RO_CLEAN_AIR_FACTOR);
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val / 10;                //calculate the average value

  val = val / RO_CLEAN_AIR_FACTOR; //divided by RO_CLEAN_AIR_FACTOR yields the Ro
  //according to the chart in the datasheet
  return val;
}
/**************************************************************************************/
float GetRo(float *P1, float *P2, float ppm, float Rs, float a, float b)
{
  float   Ro = Rs * (pow((a / ppm), (1 / b)));
  return Ro;
}
/**************************************************************************************/
float Geta(float *P1, float a, float b)
{
  a = P1[0] / (pow(P1[1], b));
  return a;
}
/**************************************************************************************/
float Getb(float *P1, float *P2, float b)
{
  b = log( P1[0] / P2[0]) / log(P1[1] / P2[1]);
  return b;
}
/**************************************************************************************/
float Getppm(float rs_ro_ratio, float a, float b)
{
  ppm = a * pow(rs_ro_ratio, b);
  return ppm;
}

