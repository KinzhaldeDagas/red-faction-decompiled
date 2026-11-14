// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005733E0 rf_renderer_set_channel_sum_color_filter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl(enableByte,redWeight,greenWeight,blueWeight). Always stores raw byte187CD04 and returns same byte throughAL. Only when nonzero copies three float coefficients to187CD08/CD0C/CD10;disable leaves prior coefficients intact and does not load/store supplied floats. Primitive consumers gate5D2B90 with enable flag: captures ORIGINAL signed R+G+B sum once,then each output=int(sum*itsWeight),clamped0..255. No division by3 or multiplication of each original channel by its own weight. State update only,no immediate device call,cache invalidation,normalization,finite or weight-range guard.
unsigned __int8 __cdecl rf_renderer_set_channel_sum_color_filter(
        unsigned __int8 enabled,
        float red_weight,
        float green_weight,
        float blue_weight)
{
  unsigned __int8 result; // al

  result = enabled;
  byte_187CD04 = enabled;
  if ( enabled )
  {
    flt_187CD08 = red_weight;
    flt_187CD0C = green_weight;
    flt_187CD10 = blue_weight;
  }
  return result;
}

