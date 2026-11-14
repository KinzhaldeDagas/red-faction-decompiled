// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B9AB0 rf_object_update_attachment_ancestors_once
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): Two cdecl arguments (object, bookkeeping integer). If common DWORD+124 bit0x1000000 already set, returns immediately. Otherwise resolves full parent
// handle DWORD+512 via40CE70; if valid, recursively calls itself with SAME bookkeeping integer. The local increment of that integer happens AFTER recursion and has no externally
// observed effect. If resolved parent has common bit0x4000000, ORs that bit into child and applies4B8AA0(child,parent). Finally sets child visited bit0x1000000 even when no parent or
// no parent change. Visited bit is set AFTER recursive descent, so this function has no cycle guard for an initially unmarked attachment cycle or depth limit. EAX is incidental on
// early/no-change paths, despite inferred pointer return.
_DWORD *__cdecl rf_object_update_attachment_ancestors_once(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // [esp+4h] [ebp-4h]

  result = a1;
  if ( ((unsigned int)&unk_1000000 & a1[31]) == 0 )
  {
    v3 = (_DWORD *)rf_object_resolve_handle(a1[128]);
    if ( v3 )
    {
      rf_object_update_attachment_ancestors_once(v3, a2);
      if ( (v3[31] & 0x4000000) != 0 )
      {
        a1[31] |= 0x4000000u;
        rf_object_apply_parent_attachment_transform(a1, (int)v3);
      }
    }
    a1[31] |= (unsigned int)&unk_1000000;
    return a1;
  }
  return result;
}

