// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518210 rf_nav_graph_prepare_request_nodes
// UNREALRED VERIFIED [combat-panic-20261104]: Runtime graph+35 is rewritten per request by5182C0; not a serialized bool. Admittednodes copy originalbase→working+0C; grounded workingY=baseY-nodeHeight*.5+agentHeight.5182C0:grounded excludes node+40!=0, then inclusive agentRadius<=node+1C and agentHeight<=node+20. Source nodes and raw geometry remain stable; working scratch separate.
// UNREALRED VERIFIED [combat-panic-bounds-20261104]: Graph working positions, eligibility and cached distances are shared source-node scratch across AI requests; only synthetic start/end/path/hints are per body. Ineligible nodes retain previous working position. Host callback reentry guards may abort overwritten scratch but must not reset sequential cross-AI state.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall graph,request,RET4. Iterates all graph pointers,uses5182C0 size/mode predicate. Admitted node:ineligible BYTE53=0,copies ORIGINAL position0 to working12,then if request grounded BYTE32==1 adjusts workingY16=workingY-node height32*0.5+request height28 with float store. Rejected node sets53=1 but does NOT refresh its working position,cost,parent or other flags. No graph/query cloning or reset of every scratch field. Return is graph count-loop residue,not status. Node working/eligibility scratch shared across sequential AI requests;earlier combat notes preserved.
int __thiscall rf_nav_graph_prepare_request_nodes(_DWORD *this, int a2)
{
  int result; // eax
  float copy_result[3]; // [esp+4h] [ebp-14h] BYREF
  float *source; // [esp+10h] [ebp-8h]
  int v6; // [esp+14h] [ebp-4h]

  v6 = 0;
  for ( result = rf_receiver_get_first_dword(this); v6 < result; result = rf_receiver_get_first_dword(this) )
  {
    source = *(float **)sub_552200(this, v6);
    if ( rf_nav_node_admits_request_dimensions((int)source, a2) )
    {
      *((_BYTE *)source + 53) = 0;
      rf_vector_copy(source + 3, copy_result, source);
      if ( *(_BYTE *)(a2 + 32) == 1 )
        source[4] = source[4] - source[8] * 0.5 + *(float *)(a2 + 28);
    }
    else
    {
      *((_BYTE *)source + 53) = 1;
    }
    ++v6;
  }
  return result;
}

