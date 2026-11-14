// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1DE0 rf_d3d8_mipmap_dimensions_supported_4_to_256
// UNREALRED VERIFIED [texture-upload-20261028]: Returnstrueonlywhen BOTHsigneddimensions exactlyin{4,8,16,32,64,128,256}. Branchesrounduptothissetthencompareoriginal; <=0,1/2,nonpowersand>256false. Doesnotquerydevicecaps.
bool __cdecl rf_d3d8_mipmap_dimensions_supported_4_to_256(int a1, int a2)
{
  int v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  if ( a1 > 4 )
  {
    if ( a1 > 8 )
    {
      if ( a1 > 16 )
      {
        if ( a1 > 32 )
        {
          if ( a1 > 64 )
          {
            if ( a1 > 128 )
              v4 = 256;
            else
              v4 = 128;
          }
          else
          {
            v4 = 64;
          }
        }
        else
        {
          v4 = 32;
        }
      }
      else
      {
        v4 = 16;
      }
    }
    else
    {
      v4 = 8;
    }
  }
  else
  {
    v4 = 4;
  }
  if ( a2 > 4 )
  {
    if ( a2 > 8 )
    {
      if ( a2 > 16 )
      {
        if ( a2 > 32 )
        {
          if ( a2 > 64 )
          {
            if ( a2 > 128 )
              v3 = 256;
            else
              v3 = 128;
          }
          else
          {
            v3 = 64;
          }
        }
        else
        {
          v3 = 32;
        }
      }
      else
      {
        v3 = 16;
      }
    }
    else
    {
      v3 = 8;
    }
  }
  else
  {
    v3 = 4;
  }
  return v4 == a1 && v3 == a2;
}

