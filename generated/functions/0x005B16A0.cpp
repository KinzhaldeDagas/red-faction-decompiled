// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B16A0 rf_aabb_select_corner_by_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Cdecl(outVector,unsigned INTEGER corner selector,boundsMin,boundsMax),16-byte caller cleanup. Corrected selector from false float* type to unsigned int; no selector pointer dereference. Cases0..7 copy XYZ through vector setter in order:max/max/min,max/min/min,min/min/min,min/max/min,max/max/max,max/min/max,min/min/max,min/max/max. Each valid case reads3 source components as by-value stack floats before setter,returns output pointer. Any selector outside unsigned0..7 performs NO write and leaves EAX equal selector bits(incidental invalid pointer in stored float* return). No index clamp,default corner,dimension ordering,NaN/pointer validation. Earlier repeatable corner-order note
// preserved.
float *__cdecl rf_aabb_select_corner_by_index(
        float *out_vector,
        unsigned int corner_index,
        const float *bounds_min,
        const float *bounds_max)
{
  float *result; // eax

  result = (float *)corner_index;
  switch ( corner_index )
  {
    case 0u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_max, bounds_max[1], bounds_min[2]);
      break;
    case 1u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_max, bounds_min[1], bounds_min[2]);
      break;
    case 2u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_min, bounds_min[1], bounds_min[2]);
      break;
    case 3u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_min, bounds_max[1], bounds_min[2]);
      break;
    case 4u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_max, bounds_max[1], bounds_max[2]);
      break;
    case 5u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_max, bounds_min[1], bounds_max[2]);
      break;
    case 6u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_min, bounds_min[1], bounds_max[2]);
      break;
    case 7u:
      result = rf_vector3_set_components_thiscall(out_vector, *bounds_min, bounds_max[1], bounds_max[2]);
      break;
    default:
      return result;
  }
  return result;
}

