// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052E860 rf_geomod_boolean_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl13 stack arguments: workspace,cutter,mode,debugBYTE,translation,matrix,outputSolid,transferMode,scaleF32,outArea,policyBYTE,deform1,deform2. RunSIGNED legacycapacityguards thresholds325faces,1500corners,1500vertices,50nodes. All4retail wrappersreturnliteral0x40000000,so guards do not imposefree-pool/hole/cumulative limits. Onadmission capture PEAK active counts for face,corner,vertex,node pools; ALL four queries reset stored peaks to current active usage. StoreglobalsworkspaceD4B88C,cutterD4B7C8,modeD4B890,transferModeD4B8E4,debugBYTED4B7D5,policyBYTED4B7D4,translationD4B7D0,matrixD4B7F0,outSolidD4B894,scaleD4B8E8,outAreaD4B8DC,deform1D4B7D8,deform2D4B7C0;setstage0. SuccessEAXremainsargument12
// deform1pointer,may0;notbool. No null/sameoperand/mode/active-operation guard, allocation or rollback: canoverwrite in-flightglobalcontext. Hypotheticalguardfailure returnsincidental lastguard/EAXanddoesnotresetstage; retailguardsalwayspass.
int __cdecl rf_geomod_boolean_init(
        int a1,
        int a2,
        int a3,
        char a4,
        int a5,
        int a6,
        int a7,
        int a8,
        float a9,
        int a10,
        char a11,
        int a12,
        int a13)
{
  int result; // eax
  bool v14; // [esp+3h] [ebp-1h]

  v14 = rf_geomod_face_pool_capacity_guard() < 325;
  if ( rf_geomod_corner_pool_capacity_guard() < 1500 )
    v14 = 1;
  if ( rf_geomod_vertex_pool_capacity_guard() < 1500 )
    v14 = 1;
  result = rf_geomod_spatial_node_pool_capacity_guard();
  if ( result < 50 )
  {
    result = 0;
    v14 = 1;
  }
  if ( !v14 )
  {
    rf_geomod_boolean_initial_face_used_telemetry = rf_geomod_face_pool_take_peak_used_count();
    rf_geomod_boolean_initial_corner_used_telemetry = rf_geomod_corner_pool_take_peak_used_count();
    rf_geomod_boolean_initial_vertex_used_telemetry = rf_geomod_vertex_pool_take_peak_used_count();
    rf_geomod_boolean_initial_spatial_node_used_telemetry = rf_geomod_spatial_node_pool_take_peak_used_count();
    dword_D4B88C = a1;
    unk_D4B7C8 = a2;
    dword_D4B890 = a3;
    unk_D4B8E4 = a8;
    unk_D4B7D5 = a4;
    unk_D4B7D4 = a11;
    unk_D4B7D0 = a5;
    unk_D4B7F0 = a6;
    unk_D4B894 = a7;
    unk_D4B8E8 = a9;
    unk_D4B8DC = a10;
    unk_D4B7D8 = a12;
    unk_D4B7C0 = a13;
    rf_geomod_boolean_stage = 0;
    return a12;
  }
  return result;
}

