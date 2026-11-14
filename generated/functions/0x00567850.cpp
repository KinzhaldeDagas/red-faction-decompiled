// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567850 rf_atan_ratio_with_negative_x_pi_adjustment
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments y,x. If x==0,returns0 when y==0,else +/-pi/2 according to ypositive. Otherwise float-rounds y/x,passes to0x43C8B0 actualarctangent wrapper,and adds pi when x<0. Does not subtract pi for negativey/negativex; result may be in(pi,3pi/2). Current prior log-named callee was misidentified,now corrected. Returns float-rounded value. Not identical to standard atan2 outputrange.
double __cdecl rf_atan_ratio_with_negative_x_pi_adjustment(float a1, float a2)
{
  float v3; // [esp+4h] [ebp-8h]
  float v5; // [esp+8h] [ebp-4h]

  if ( a2 == 0.0 )
  {
    if ( a1 == 0.0 )
    {
      return (float)0.0;
    }
    else if ( a1 <= 0.0 )
    {
      return (float)-1.5707964;
    }
    else
    {
      return (float)1.5707964;
    }
  }
  else
  {
    v3 = a1 / a2;
    v5 = rf_atan_float_wrapper(v3);
    if ( a2 < 0.0 )
      return (float)(v5 + 3.141592741012573);
    return v5;
  }
}

