// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F8F70 rf_mission_event_delete_by_subtype
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Reads subtype at E+656 BEFORE any null test; caller must supply valid event. Dispatches nonvirtual scalar deleting destructor with flags1, releasing event allocation. Subtype0 destroys RF strings696/704;10,28 string700;15,32 string704;33 strings704/712;12,21,22,36,37,41,70 string696. Other explicitly handled subtypes use base-only wrapper; default uses base-members wrapper. Both base paths destroy base members then free. Does not unregister E in this body; object-delete path handles removal separately. Return register is incidental original/freed pointer, not success status.
_DWORD *__cdecl rf_mission_event_delete_by_subtype(_DWORD *a1)
{
  _DWORD *result; // eax

  result = a1;
  switch ( a1[164] )
  {
    case 0:
      if ( a1 )
        result = rf_mission_event_scalar_delete_two_strings_696_704(a1, 1);
      break;
    case 1:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 5:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 6:
      if ( a1 )
        goto LABEL_139;
      break;
    case 7:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 9:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0xA:
      if ( a1 )
        goto LABEL_18;
      break;
    case 0xB:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0xC:
      result = a1;
      if ( a1 )
        goto LABEL_116;
      break;
    case 0xD:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0xE:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0xF:
      result = a1;
      if ( a1 )
        goto LABEL_32;
      break;
    case 0x10:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x11:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x12:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x13:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x14:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x15:
      result = a1;
      if ( a1 )
        goto LABEL_116;
      break;
    case 0x16:
      if ( a1 )
        goto LABEL_116;
      break;
    case 0x17:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x18:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x1C:
      result = a1;
      if ( a1 )
LABEL_18:
        result = rf_mission_event_scalar_delete_string_700(a1, 1);
      break;
    case 0x1E:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x1F:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x20:
      result = a1;
      if ( a1 )
LABEL_32:
        result = rf_mission_event_scalar_delete_string_704(a1, 1);
      break;
    case 0x21:
      if ( a1 )
        result = rf_mission_event_scalar_delete_two_strings_704_712((char *)a1, 1);
      break;
    case 0x22:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x23:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x24:
      result = a1;
      if ( a1 )
        goto LABEL_116;
      break;
    case 0x25:
      result = a1;
      if ( a1 )
        goto LABEL_116;
      break;
    case 0x26:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x28:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x29:
      result = a1;
      if ( a1 )
        goto LABEL_116;
      break;
    case 0x2A:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x2C:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x2D:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x2E:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x2F:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x31:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x32:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x39:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x3A:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x3B:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x3D:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x42:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x45:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x46:
      if ( a1 )
LABEL_116:
        result = rf_mission_event_scalar_delete_string_696(a1, 1);
      break;
    case 0x47:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x48:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x49:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x54:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x55:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x57:
      result = a1;
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x58:
      if ( a1 )
        goto LABEL_139;
      break;
    case 0x59:
      result = a1;
      if ( a1 )
LABEL_139:
        result = rf_mission_event_scalar_delete_base_only(a1, 1);
      break;
    default:
      result = a1;
      if ( a1 )
        result = rf_mission_event_scalar_delete_base_members((void **)a1, 1);
      break;
  }
  return result;
}

