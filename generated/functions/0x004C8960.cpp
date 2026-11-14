// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C8960 rf_glass_general_quad_face_tessellate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl(face,impactPosition,optionalDirection,suppliedRoom). Valid quad assumed, no own corner/planarity/convexity test.
// P0=head.vertex,P1=head.next.vertex,P3=head.prev.vertex,P2=head.next.next.vertex. E0=P1-P0,E1=P2-P1,E2=P3-P0,E3=P2-P3; lengths L0..L3 binary32. Face frame
// forward=-normal,up=normalize(E0),AABB center saved. Primary edge selector tests candidates0,1,2 in order, accepting only when ALL three other lengths are ORDERED <=candidate. Else
// chooses3 unconditionally. Finite ties choose first max; ANY NaN length rejects candidates0..2 and selects3. Native TEST AH41/JP treats unordered as outranking, unlike ordinary
// ordered > pseudocode.
// Four32B GLOBAL edge records A822724,B822744,C823B80,D823BA0 have startXYZ,unitDirectionXYZ,length,originalEdgeId. Define +eK=normalize(EK),-eK=negated normalization. H means STRICT
// ORDERED greater OR unordered, not only >. For primary0/3 H=(L1>L2 ORunordered); primary1/2 H=(L3>L0 ORunordered). Exact setup (A;B;C;D), each entry(start,direction,edgeId/length):
// primary0,Hfalse: (P0,+e0,0);(P0,+e2,2);(P3,+e3,3);(P1,+e1,1). primary0,Htrue: (P1,-e0,0);(P1,+e1,1);(P2,-e3,3);(P0,+e2,2).
// primary1,Hfalse: (P1,+e1,1);(P1,-e0,0);(P0,+e2,2);(P2,-e3,3). primary1,Htrue: (P1,+e1,1);(P2,-e3,3);(P3,-e2,2);(P1,-e0,0).
// primary2,Hfalse: (P0,+e2,2);(P0,+e0,0);(P1,+e1,1);(P3,+e3,3). primary2,Htrue: (P0,+e2,2);(P3,+e3,3);(P2,-e1,1);(P0,+e0,0).
// primary3,Hfalse: (P3,+e3,3);(P3,-e2,2);(P0,+e0,0);(P2,-e1,1). primary3,Htrue: (P2,-e3,3);(P2,-e1,1);(P1,-e0,0);(P3,-e2,2). A/B/C/D origins are literal; do not force them to share
// assumed grid corners. Switch table4CA5C0 has4 entries in primary order.
// Counts Nx=min(floor(F32(A.length*4))+2,16),Ny analogB.length,globals822308/8222C8; no lower/finite/overflow guard. Global grid822768 address320*i+20*j is WORLD XYZ+UV from outset.
// A edge fills(i,0),i0..Nx-1, jitter only non-endpoints,stepA=LA/(Nx-1). B fills(0,j),j1..Ny-1: jitter suppression tests STALE completed i==1 OR i==Ny-1 (i==Nx for ordinary positive
// loops), not currentj, so entire B side jitter/no-jitter depends on dimension relation. C fills(i,Ny-1),i1..Nx-1 using stepC=LC/(Nx-1),skips jitter at i==1 OR i==Nx-1,including
// first INTERIOR i1. D fills(Nx-1,j),j1..Ny-2 using stepD=LD/(Ny-1): again tests STALE i==1 OR i==Ny-2,not j. Preserve these native loop-index asymmetries, RNG consumption and corner
// overwrites.
// Interior i1..Nx-2: normalize vector grid(i,Ny-1)-grid(i,0),rowStep=length/(Ny-1). For each interiorj: sample jitter along GLOBAL C.direction*stepC FIRST, then along normalized
// column vector*rowStep; point=grid(i,0)+columnDir*(j*rowStep)+columnDir*jitter2+C.dir*jitter1 using sequential F32 vector helpers. No rectangular local-grid transform or bilinear
// four-corner parameterization. All jitter uses random[-F32.45,+F32.45].
// UV uses WORLD X/Y: U=F32((original U2-U0)*grid.worldX/A.length+U0),V=F32((original V2-V0)*grid.worldY/B.length+V0). No subtraction of chosen origin, inverse basis transform or
// remapping of UV corners when primary edge changes; distinct from local-coordinate rectangular7990 path. No zero-edge division guard; global scratch not reentrant.
// Common cell/ownership tail shared with the other tessellator: before allocation, traverses ALL existing buckets; shards whose attachment-owner100 equals face.owner68 get random
// axis76,spin88=random[pi,2pi],budget96=floor(random[3,6]),owner100=NULL, then directional launch8840 if direction nonnull else radial73B0(mode0). Existing flags196 not reset. Scans
// worldSolid array156, each element pointer-array108; if any member equals face.owner68 AND differs from supplied room, enables per-cell room resolution. No validation of these
// arrays/owners. Existing-shard reactivation and global grid writes precede all new allocations.
// For each cell i,j, allocator85A0(&shard,suppliedRoom) return BYTE(fresh1/recycled0) is stored but NOT used as success; only output pointerNULL guard exists. Copies four WORLD
// XYZ+UV20B grid vertices in order(i,j),(i,j+1),(i+1,j+1),(i+1,j) to shard116/136/156/176. Flags196=0,center8=sequential sum of four points*.25,orientation20=constructed face frame.
// Radius92 starts fast_distance(vertex0,center) then replaces only when STRICT ORDERED current<candidate for vertices1..3; first NaN sticks, later NaN ignored. Room104 initially
// supplied room; if room-resolution flag set, resolve(world,suppliedRoom,faceAABBcenter,shardCenter,0), store result. NULL resolution releases allocated/recycled node to FREE
// (count--), no owner bucket link/rollback of previously evicted shard. Otherwise bucket-link, inverse-translate/rotate four positions into shard frame (UV unchanged),RGBA56 raw
// white,random axis76,spin88=random[pi,2pi],budget96=floor(random[3,6]),owner100=NULL,bitmap60=shared big-glass handle; launch directional or radial mode0. No pane geometry deletion
// here, allocator-byte failure handling, full record memset or rollback of previous cells/old-shard reactivation. Valid counts<=16 yield at most225 four-corner cells, not 450
// independent triangular shards. Return AL incidental loop/backend/allocator value, not number of cells or reliable bool.
char __cdecl rf_glass_general_quad_face_tessellate(int a1, float *a2, float *a3, void *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  const float *v8; // eax
  const float *v9; // eax
  const float *v10; // eax
  const float *v11; // eax
  const float *v12; // eax
  const float *v13; // eax
  const float *v14; // eax
  const float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  const float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  float *v21; // eax
  float *v22; // eax
  float *v23; // eax
  float *v24; // eax
  const float *v25; // eax
  float *v26; // eax
  float *v27; // eax
  float *v28; // eax
  float *v29; // eax
  float *v30; // eax
  float *v31; // eax
  const float *v32; // eax
  const float *v33; // eax
  const float *v34; // eax
  const float *v35; // eax
  const float *v36; // eax
  float *v37; // eax
  float *v38; // eax
  float *v39; // eax
  float *v40; // eax
  float *v41; // eax
  float *v42; // eax
  const float *v43; // eax
  float *v44; // eax
  float *v45; // eax
  float *v46; // eax
  float *v47; // eax
  float *v48; // eax
  float *v49; // eax
  float *v50; // eax
  float *v51; // eax
  float *v52; // eax
  float *v53; // eax
  double v54; // st7
  float *v55; // eax
  float *v56; // eax
  float *v57; // eax
  float *v58; // eax
  float *v59; // eax
  double v60; // st7
  float *v61; // eax
  float *v62; // eax
  float *v63; // eax
  float *v64; // eax
  float *v65; // eax
  double v66; // st7
  float *v67; // eax
  float *v68; // eax
  float *v69; // eax
  float *v70; // eax
  float *v71; // eax
  double v72; // st7
  float *v73; // eax
  float *v74; // eax
  float *v75; // eax
  float *v76; // eax
  double v77; // st7
  double v78; // st7
  double v79; // st7
  float *v80; // eax
  float *v81; // eax
  float *v82; // eax
  float *v83; // eax
  double v84; // st7
  double v85; // st7
  int first_dword; // eax
  float *v87; // eax
  void *v88; // eax
  float *v89; // eax
  double v90; // st7
  double v91; // st7
  float *scalar; // [esp+8h] [ebp-8A8h]
  float *value; // [esp+10h] [ebp-8A0h]
  float *valuea; // [esp+10h] [ebp-8A0h]
  float *valueb; // [esp+10h] [ebp-8A0h]
  float *valuec; // [esp+10h] [ebp-8A0h]
  float *valued; // [esp+10h] [ebp-8A0h]
  float valuee; // [esp+10h] [ebp-8A0h]
  float valuef; // [esp+10h] [ebp-8A0h]
  float *v101; // [esp+14h] [ebp-89Ch]
  float v102; // [esp+18h] [ebp-898h]
  float v103; // [esp+1Ch] [ebp-894h]
  float v104; // [esp+20h] [ebp-890h]
  float v105; // [esp+2Ch] [ebp-884h]
  float v106; // [esp+30h] [ebp-880h]
  float v107; // [esp+34h] [ebp-87Ch]
  float v108; // [esp+3Ch] [ebp-874h]
  float v109; // [esp+40h] [ebp-870h]
  float v110; // [esp+44h] [ebp-86Ch]
  float v111; // [esp+4Ch] [ebp-864h]
  float v112; // [esp+50h] [ebp-860h]
  float v113; // [esp+54h] [ebp-85Ch]
  float v114; // [esp+58h] [ebp-858h]
  float v115; // [esp+5Ch] [ebp-854h]
  float v116; // [esp+60h] [ebp-850h]
  float v117; // [esp+68h] [ebp-848h]
  float v118; // [esp+70h] [ebp-840h]
  _BYTE v119[4]; // [esp+78h] [ebp-838h] BYREF
  float v120[3]; // [esp+7Ch] [ebp-834h] BYREF
  float v121[3]; // [esp+88h] [ebp-828h] BYREF
  float v122[3]; // [esp+94h] [ebp-81Ch] BYREF
  float v123[3]; // [esp+A0h] [ebp-810h] BYREF
  float v124[3]; // [esp+ACh] [ebp-804h] BYREF
  float v125[3]; // [esp+B8h] [ebp-7F8h] BYREF
  float v126[3]; // [esp+C4h] [ebp-7ECh] BYREF
  float v127[3]; // [esp+D0h] [ebp-7E0h] BYREF
  float v128[3]; // [esp+DCh] [ebp-7D4h] BYREF
  float v129[3]; // [esp+E8h] [ebp-7C8h] BYREF
  float v130[3]; // [esp+F4h] [ebp-7BCh] BYREF
  float v131[3]; // [esp+100h] [ebp-7B0h] BYREF
  float v132[3]; // [esp+10Ch] [ebp-7A4h] BYREF
  float v133[3]; // [esp+118h] [ebp-798h] BYREF
  float v134[3]; // [esp+124h] [ebp-78Ch] BYREF
  float v135[3]; // [esp+130h] [ebp-780h] BYREF
  float v136[3]; // [esp+13Ch] [ebp-774h] BYREF
  float v137[3]; // [esp+148h] [ebp-768h] BYREF
  float v138[3]; // [esp+154h] [ebp-75Ch] BYREF
  float v139[3]; // [esp+160h] [ebp-750h] BYREF
  float v140[3]; // [esp+16Ch] [ebp-744h] BYREF
  float v141[3]; // [esp+178h] [ebp-738h] BYREF
  float v142[3]; // [esp+184h] [ebp-72Ch] BYREF
  float v143[3]; // [esp+190h] [ebp-720h] BYREF
  float v144[3]; // [esp+19Ch] [ebp-714h] BYREF
  float v145[3]; // [esp+1A8h] [ebp-708h] BYREF
  float v146[3]; // [esp+1B4h] [ebp-6FCh] BYREF
  float v147[3]; // [esp+1C0h] [ebp-6F0h] BYREF
  float v148[3]; // [esp+1CCh] [ebp-6E4h] BYREF
  float v149[3]; // [esp+1D8h] [ebp-6D8h] BYREF
  float v150[3]; // [esp+1E4h] [ebp-6CCh] BYREF
  float v151[3]; // [esp+1F0h] [ebp-6C0h] BYREF
  float v152[3]; // [esp+1FCh] [ebp-6B4h] BYREF
  float v153[3]; // [esp+208h] [ebp-6A8h] BYREF
  float v154[3]; // [esp+214h] [ebp-69Ch] BYREF
  float v155[3]; // [esp+220h] [ebp-690h] BYREF
  float v156[3]; // [esp+22Ch] [ebp-684h] BYREF
  float v157[3]; // [esp+238h] [ebp-678h] BYREF
  float v158[3]; // [esp+244h] [ebp-66Ch] BYREF
  float v159[3]; // [esp+250h] [ebp-660h] BYREF
  float v160[3]; // [esp+25Ch] [ebp-654h] BYREF
  float v161[3]; // [esp+268h] [ebp-648h] BYREF
  float v162[3]; // [esp+274h] [ebp-63Ch] BYREF
  float v163[3]; // [esp+280h] [ebp-630h] BYREF
  float v164[3]; // [esp+28Ch] [ebp-624h] BYREF
  _BYTE v165[12]; // [esp+298h] [ebp-618h] BYREF
  float v166[3]; // [esp+2A4h] [ebp-60Ch] BYREF
  float v167[3]; // [esp+2B0h] [ebp-600h] BYREF
  float v168[3]; // [esp+2BCh] [ebp-5F4h] BYREF
  _BYTE v169[12]; // [esp+2C8h] [ebp-5E8h] BYREF
  float v170[3]; // [esp+2D4h] [ebp-5DCh] BYREF
  float v171[3]; // [esp+2E0h] [ebp-5D0h] BYREF
  float v172[3]; // [esp+2ECh] [ebp-5C4h] BYREF
  _BYTE v173[12]; // [esp+2F8h] [ebp-5B8h] BYREF
  float v174[3]; // [esp+304h] [ebp-5ACh] BYREF
  float v175[3]; // [esp+310h] [ebp-5A0h] BYREF
  float v176[3]; // [esp+31Ch] [ebp-594h] BYREF
  _BYTE v177[12]; // [esp+328h] [ebp-588h] BYREF
  float v178[3]; // [esp+334h] [ebp-57Ch] BYREF
  float v179[3]; // [esp+340h] [ebp-570h] BYREF
  _BYTE v180[12]; // [esp+34Ch] [ebp-564h] BYREF
  float v181[3]; // [esp+358h] [ebp-558h] BYREF
  float v182[3]; // [esp+364h] [ebp-54Ch] BYREF
  float v183[3]; // [esp+370h] [ebp-540h] BYREF
  _BYTE v184[12]; // [esp+37Ch] [ebp-534h] BYREF
  float v185[3]; // [esp+388h] [ebp-528h] BYREF
  float v186[3]; // [esp+394h] [ebp-51Ch] BYREF
  float v187[3]; // [esp+3A0h] [ebp-510h] BYREF
  _BYTE v188[12]; // [esp+3ACh] [ebp-504h] BYREF
  float v189[3]; // [esp+3B8h] [ebp-4F8h] BYREF
  float v190[3]; // [esp+3C4h] [ebp-4ECh] BYREF
  float v191[3]; // [esp+3D0h] [ebp-4E0h] BYREF
  _BYTE v192[12]; // [esp+3DCh] [ebp-4D4h] BYREF
  float v193[3]; // [esp+3E8h] [ebp-4C8h] BYREF
  float v194[3]; // [esp+3F4h] [ebp-4BCh] BYREF
  _BYTE v195[12]; // [esp+400h] [ebp-4B0h] BYREF
  float v196[3]; // [esp+40Ch] [ebp-4A4h] BYREF
  float v197[3]; // [esp+418h] [ebp-498h] BYREF
  _BYTE v198[12]; // [esp+424h] [ebp-48Ch] BYREF
  float v199[3]; // [esp+430h] [ebp-480h] BYREF
  float v200[3]; // [esp+43Ch] [ebp-474h] BYREF
  _BYTE v201[12]; // [esp+448h] [ebp-468h] BYREF
  float v202[3]; // [esp+454h] [ebp-45Ch] BYREF
  float v203[3]; // [esp+460h] [ebp-450h] BYREF
  _BYTE v204[12]; // [esp+46Ch] [ebp-444h] BYREF
  float v205[3]; // [esp+478h] [ebp-438h] BYREF
  float v206[3]; // [esp+484h] [ebp-42Ch] BYREF
  _BYTE v207[12]; // [esp+490h] [ebp-420h] BYREF
  float v208[3]; // [esp+49Ch] [ebp-414h] BYREF
  float v209[3]; // [esp+4A8h] [ebp-408h] BYREF
  float v210[3]; // [esp+4B4h] [ebp-3FCh] BYREF
  _BYTE v211[12]; // [esp+4C0h] [ebp-3F0h] BYREF
  float v212[3]; // [esp+4CCh] [ebp-3E4h] BYREF
  float v213[3]; // [esp+4D8h] [ebp-3D8h] BYREF
  float v214[3]; // [esp+4E4h] [ebp-3CCh] BYREF
  _BYTE v215[12]; // [esp+4F0h] [ebp-3C0h] BYREF
  float v216[3]; // [esp+4FCh] [ebp-3B4h] BYREF
  float v217[3]; // [esp+508h] [ebp-3A8h] BYREF
  float v218[3]; // [esp+514h] [ebp-39Ch] BYREF
  _BYTE v219[12]; // [esp+520h] [ebp-390h] BYREF
  float v220[3]; // [esp+52Ch] [ebp-384h] BYREF
  float v221[3]; // [esp+538h] [ebp-378h] BYREF
  _BYTE v222[12]; // [esp+544h] [ebp-36Ch] BYREF
  float v223[3]; // [esp+550h] [ebp-360h] BYREF
  float v224[3]; // [esp+55Ch] [ebp-354h] BYREF
  float v225[3]; // [esp+568h] [ebp-348h] BYREF
  _BYTE v226[12]; // [esp+574h] [ebp-33Ch] BYREF
  float v227[3]; // [esp+580h] [ebp-330h] BYREF
  float v228[3]; // [esp+58Ch] [ebp-324h] BYREF
  float v229[3]; // [esp+598h] [ebp-318h] BYREF
  _BYTE v230[12]; // [esp+5A4h] [ebp-30Ch] BYREF
  float v231[3]; // [esp+5B0h] [ebp-300h] BYREF
  float v232[3]; // [esp+5BCh] [ebp-2F4h] BYREF
  float v233[3]; // [esp+5C8h] [ebp-2E8h] BYREF
  _BYTE v234[12]; // [esp+5D4h] [ebp-2DCh] BYREF
  float v235[3]; // [esp+5E0h] [ebp-2D0h] BYREF
  float v236[3]; // [esp+5ECh] [ebp-2C4h] BYREF
  _BYTE v237[12]; // [esp+5F8h] [ebp-2B8h] BYREF
  float v238[3]; // [esp+604h] [ebp-2ACh] BYREF
  float v239[3]; // [esp+610h] [ebp-2A0h] BYREF
  float v240[3]; // [esp+61Ch] [ebp-294h] BYREF
  _BYTE v241[12]; // [esp+628h] [ebp-288h] BYREF
  float v242[3]; // [esp+634h] [ebp-27Ch] BYREF
  float v243[3]; // [esp+640h] [ebp-270h] BYREF
  _BYTE v244[12]; // [esp+64Ch] [ebp-264h] BYREF
  float v245[3]; // [esp+658h] [ebp-258h] BYREF
  float v246[3]; // [esp+664h] [ebp-24Ch] BYREF
  _BYTE v247[12]; // [esp+670h] [ebp-240h] BYREF
  float v248[3]; // [esp+67Ch] [ebp-234h] BYREF
  float v249[3]; // [esp+688h] [ebp-228h] BYREF
  _BYTE v250[12]; // [esp+694h] [ebp-21Ch] BYREF
  float v251[3]; // [esp+6A0h] [ebp-210h] BYREF
  float v252[3]; // [esp+6ACh] [ebp-204h] BYREF
  _BYTE v253[12]; // [esp+6B8h] [ebp-1F8h] BYREF
  float v254[3]; // [esp+6C4h] [ebp-1ECh] BYREF
  float v255[3]; // [esp+6D0h] [ebp-1E0h] BYREF
  _BYTE v256[12]; // [esp+6DCh] [ebp-1D4h] BYREF
  float v257[3]; // [esp+6E8h] [ebp-1C8h] BYREF
  float v258[3]; // [esp+6F4h] [ebp-1BCh] BYREF
  _BYTE v259[12]; // [esp+700h] [ebp-1B0h] BYREF
  float v260[3]; // [esp+70Ch] [ebp-1A4h] BYREF
  float v261[3]; // [esp+718h] [ebp-198h] BYREF
  _BYTE v262[12]; // [esp+724h] [ebp-18Ch] BYREF
  float v263[3]; // [esp+730h] [ebp-180h] BYREF
  float v264[3]; // [esp+73Ch] [ebp-174h] BYREF
  _BYTE v265[12]; // [esp+748h] [ebp-168h] BYREF
  float v266[3]; // [esp+754h] [ebp-15Ch] BYREF
  float v267[3]; // [esp+760h] [ebp-150h] BYREF
  float v268[3]; // [esp+76Ch] [ebp-144h] BYREF
  float v269[3]; // [esp+778h] [ebp-138h] BYREF
  float copy_result[3]; // [esp+784h] [ebp-12Ch] BYREF
  float v271[3]; // [esp+790h] [ebp-120h] BYREF
  float sum_result[3]; // [esp+79Ch] [ebp-114h] BYREF
  float v273; // [esp+7A8h] [ebp-108h]
  int m; // [esp+7ACh] [ebp-104h]
  float v275; // [esp+7B0h] [ebp-100h]
  char v276; // [esp+7B7h] [ebp-F9h]
  void *v277; // [esp+7B8h] [ebp-F8h]
  int v278; // [esp+7BCh] [ebp-F4h]
  float lhs[3]; // [esp+7C0h] [ebp-F0h] BYREF
  int j; // [esp+7CCh] [ebp-E4h]
  float v281[3]; // [esp+7D0h] [ebp-E0h] BYREF
  float out_vector[3]; // [esp+7DCh] [ebp-D4h] BYREF
  float v283[3]; // [esp+7E8h] [ebp-C8h] BYREF
  float v284[3]; // [esp+7F4h] [ebp-BCh] BYREF
  float v285; // [esp+800h] [ebp-B0h]
  int v286; // [esp+804h] [ebp-ACh]
  float vector[3]; // [esp+808h] [ebp-A8h] BYREF
  float scaled_result[3]; // [esp+814h] [ebp-9Ch] BYREF
  float **v289; // [esp+820h] [ebp-90h]
  float v290; // [esp+824h] [ebp-8Ch]
  float v291; // [esp+828h] [ebp-88h]
  int v292; // [esp+82Ch] [ebp-84h]
  float v293[3]; // [esp+830h] [ebp-80h] BYREF
  float v294[3]; // [esp+83Ch] [ebp-74h] BYREF
  float v295; // [esp+848h] [ebp-68h]
  float source[3]; // [esp+84Ch] [ebp-64h] BYREF
  float v297; // [esp+858h] [ebp-58h]
  float **v298; // [esp+85Ch] [ebp-54h]
  float destination[3]; // [esp+860h] [ebp-50h] BYREF
  float v300[6]; // [esp+86Ch] [ebp-44h] BYREF
  int v301; // [esp+884h] [ebp-2Ch]
  float v302; // [esp+888h] [ebp-28h]
  char v303; // [esp+88Fh] [ebp-21h]
  float *k; // [esp+890h] [ebp-20h] BYREF
  int v305; // [esp+894h] [ebp-1Ch]
  float v306; // [esp+898h] [ebp-18h]
  int i; // [esp+89Ch] [ebp-14h]
  float rhs[3]; // [esp+8A0h] [ebp-10h] BYREF
  float v309; // [esp+8ACh] [ebp-4h]

  v4 = rf_vector_add((const float *)(a1 + 28), sum_result, (const float *)(a1 + 16));
  rf_vector_multiply_scalar(v4, scaled_result, 0.5);
  v301 = *(_DWORD *)(a1 + 64);
  v289 = *(float ***)(*(_DWORD *)(a1 + 64) + 20);
  v298 = *(float ***)(*(_DWORD *)(a1 + 64) + 24);
  v305 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 64) + 20) + 20);
  rf_vector3_copy_return_destination(rhs, *(float **)v301);
  rf_vector3_copy_return_destination(lhs, *v289);
  rf_vector3_copy_return_destination(source, *v298);
  rf_vector3_copy_return_destination(v294, *(float **)v305);
  rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_subtract(v294, v281, lhs);
  rf_vector_subtract(source, v283, rhs);
  rf_vector_subtract(v294, v284, source);
  rf_matrix3_construct((char *)destination);
  v5 = rf_vector_subtract(source, v271, rhs);
  rf_vector_copy(destination, copy_result, v5);
  v6 = rf_vector_subtract(lhs, v269, rhs);
  rf_vector_copy(v300, v268, v6);
  rf_vector_normalize(v300);
  v7 = rf_vector_negate((float *)a1, v267);
  rf_orientation_from_forward_and_up_hint(destination, v7, v300);
  v290 = rf_vector3_length(out_vector);
  v302 = rf_vector3_length(v281);
  v306 = rf_vector3_length(v283);
  v291 = rf_vector3_length(v284);
  if ( v302 > (double)v290 || v306 > (double)v290 || v291 > (double)v290 )
  {
    if ( v290 > (double)v302 || v306 > (double)v302 || v291 > (double)v302 )
    {
      if ( v290 > (double)v306 || v302 > (double)v306 || v291 > (double)v306 )
      {
        rf_vector_copy(&flt_822724, v257, source);
        v11 = (const float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v256);
        rf_vector_copy(&flt_822730, v255, v11);
        unk_82273C = v291;
        unk_822740 = 3;
      }
      else
      {
        rf_vector_copy(&flt_822724, v260, rhs);
        v10 = (const float *)rf_vector3_normalized_copy_or_unit_x(v283, (int)v259);
        rf_vector_copy(&flt_822730, v258, v10);
        unk_82273C = v306;
        unk_822740 = 2;
      }
    }
    else
    {
      rf_vector_copy(&flt_822724, v263, lhs);
      v9 = (const float *)rf_vector3_normalized_copy_or_unit_x(v281, (int)v262);
      rf_vector_copy(&flt_822730, v261, v9);
      unk_82273C = v302;
      unk_822740 = 1;
    }
  }
  else
  {
    rf_vector_copy(&flt_822724, v266, rhs);
    v8 = (const float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v265);
    rf_vector_copy(&flt_822730, v264, v8);
    unk_82273C = v290;
    unk_822740 = 0;
  }
  switch ( unk_822740 )
  {
    case 0:
      if ( v302 > (double)v306 )
      {
        rf_vector_copy(&flt_822744, v245, lhs);
        v15 = (const float *)rf_vector3_normalized_copy_or_unit_x(v281, (int)v244);
        rf_vector_copy(&flt_822750, v243, v15);
        unk_82275C = v302;
        unk_822760 = 1;
        rf_vector_copy(&flt_822724, v242, lhs);
        v16 = (float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v241);
        v17 = rf_vector_negate(v16, v240);
        rf_vector_copy(&flt_822730, v239, v17);
        rf_vector_copy(&flt_823BA0, v238, rhs);
        v18 = (const float *)rf_vector3_normalized_copy_or_unit_x(v283, (int)v237);
        rf_vector_copy(&flt_823BAC, v236, v18);
        unk_823BB8 = v306;
        unk_823BBC = 2;
        rf_vector_copy(&flt_823B80, v235, v294);
        v19 = (float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v234);
        v20 = rf_vector_negate(v19, v233);
        rf_vector_copy(&flt_823B8C, v232, v20);
      }
      else
      {
        rf_vector_copy(&flt_822744, v254, rhs);
        v12 = (const float *)rf_vector3_normalized_copy_or_unit_x(v283, (int)v253);
        rf_vector_copy(&flt_822750, v252, v12);
        unk_82275C = v306;
        unk_822760 = 2;
        rf_vector_copy(&flt_823BA0, v251, lhs);
        v13 = (const float *)rf_vector3_normalized_copy_or_unit_x(v281, (int)v250);
        rf_vector_copy(&flt_823BAC, v249, v13);
        unk_823BB8 = v302;
        unk_823BBC = 1;
        rf_vector_copy(&flt_823B80, v248, source);
        v14 = (const float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v247);
        rf_vector_copy(&flt_823B8C, v246, v14);
      }
      unk_823B98 = v291;
      unk_823B9C = 3;
      break;
    case 1:
      if ( v291 > (double)v290 )
      {
        rf_vector_copy(&flt_822744, v220, v294);
        v26 = (float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v219);
        v27 = rf_vector_negate(v26, v218);
        rf_vector_copy(&flt_822750, v217, v27);
        unk_82275C = v291;
        unk_822760 = 3;
        rf_vector_copy(&flt_823BA0, v216, lhs);
        v28 = (float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v215);
        v29 = rf_vector_negate(v28, v214);
        rf_vector_copy(&flt_823BAC, v213, v29);
        unk_823BB8 = v290;
        unk_823BBC = 0;
        rf_vector_copy(&flt_823B80, v212, source);
        v30 = (float *)rf_vector3_normalized_copy_or_unit_x(v283, (int)v211);
        v31 = rf_vector_negate(v30, v210);
        rf_vector_copy(&flt_823B8C, v209, v31);
      }
      else
      {
        rf_vector_copy(&flt_822744, v231, lhs);
        v21 = (float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v230);
        v22 = rf_vector_negate(v21, v229);
        rf_vector_copy(&flt_822750, v228, v22);
        unk_82275C = v290;
        unk_822760 = 0;
        rf_vector_copy(&flt_823BA0, v227, v294);
        v23 = (float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v226);
        v24 = rf_vector_negate(v23, v225);
        rf_vector_copy(&flt_823BAC, v224, v24);
        unk_823BB8 = v291;
        unk_823BBC = 3;
        rf_vector_copy(&flt_823B80, v223, rhs);
        v25 = (const float *)rf_vector3_normalized_copy_or_unit_x(v283, (int)v222);
        rf_vector_copy(&flt_823B8C, v221, v25);
      }
      unk_823B98 = v306;
      unk_823B9C = 2;
      break;
    case 2:
      if ( v291 > (double)v290 )
      {
        rf_vector_copy(&flt_822744, v199, source);
        v35 = (const float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v198);
        rf_vector_copy(&flt_822750, v197, v35);
        unk_82275C = v291;
        unk_822760 = 3;
        rf_vector_copy(&flt_823BA0, v196, rhs);
        v36 = (const float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v195);
        rf_vector_copy(&flt_823BAC, v194, v36);
        unk_823BB8 = v290;
        unk_823BBC = 0;
        rf_vector_copy(&flt_823B80, v193, v294);
        v37 = (float *)rf_vector3_normalized_copy_or_unit_x(v281, (int)v192);
        v38 = rf_vector_negate(v37, v191);
        rf_vector_copy(&flt_823B8C, v190, v38);
      }
      else
      {
        rf_vector_copy(&flt_822744, v208, rhs);
        v32 = (const float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v207);
        rf_vector_copy(&flt_822750, v206, v32);
        unk_82275C = v290;
        unk_822760 = 0;
        rf_vector_copy(&flt_823BA0, v205, source);
        v33 = (const float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v204);
        rf_vector_copy(&flt_823BAC, v203, v33);
        unk_823BB8 = v291;
        unk_823BBC = 3;
        rf_vector_copy(&flt_823B80, v202, lhs);
        v34 = (const float *)rf_vector3_normalized_copy_or_unit_x(v281, (int)v201);
        rf_vector_copy(&flt_823B8C, v200, v34);
      }
      unk_823B98 = v302;
      unk_823B9C = 1;
      break;
    case 3:
      if ( v302 > (double)v306 )
      {
        rf_vector_copy(&flt_822744, v178, v294);
        v44 = (float *)rf_vector3_normalized_copy_or_unit_x(v281, (int)v177);
        v45 = rf_vector_negate(v44, v176);
        rf_vector_copy(&flt_822750, v175, v45);
        unk_82275C = v302;
        unk_822760 = 1;
        rf_vector_copy(&flt_822724, v174, v294);
        v46 = (float *)rf_vector3_normalized_copy_or_unit_x(v284, (int)v173);
        v47 = rf_vector_negate(v46, v172);
        rf_vector_copy(&flt_822730, v171, v47);
        rf_vector_copy(&flt_823BA0, v170, source);
        v48 = (float *)rf_vector3_normalized_copy_or_unit_x(v283, (int)v169);
        v49 = rf_vector_negate(v48, v168);
        rf_vector_copy(&flt_823BAC, v167, v49);
        unk_823BB8 = v306;
        unk_823BBC = 2;
        rf_vector_copy(&flt_823B80, v166, lhs);
        v50 = (float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v165);
        v51 = rf_vector_negate(v50, v164);
        rf_vector_copy(&flt_823B8C, v163, v51);
      }
      else
      {
        rf_vector_copy(&flt_822744, v189, source);
        v39 = (float *)rf_vector3_normalized_copy_or_unit_x(v283, (int)v188);
        v40 = rf_vector_negate(v39, v187);
        rf_vector_copy(&flt_822750, v186, v40);
        unk_82275C = v306;
        unk_822760 = 2;
        rf_vector_copy(&flt_823BA0, v185, v294);
        v41 = (float *)rf_vector3_normalized_copy_or_unit_x(v281, (int)v184);
        v42 = rf_vector_negate(v41, v183);
        rf_vector_copy(&flt_823BAC, v182, v42);
        unk_823BB8 = v302;
        unk_823BBC = 1;
        rf_vector_copy(&flt_823B80, v181, rhs);
        v43 = (const float *)rf_vector3_normalized_copy_or_unit_x(out_vector, (int)v180);
        rf_vector_copy(&flt_823B8C, v179, v43);
      }
      unk_823B98 = v290;
      unk_823B9C = 0;
      break;
    default:
      break;
  }
  v118 = unk_82273C * 4.0;
  v286 = (int)rf_floor_float(v118) + 2;
  if ( v286 > 16 )
    v286 = 16;
  unk_822308 = v286;
  v285 = unk_82273C / (double)(v286 - 1);
  v117 = unk_82275C * 4.0;
  v292 = (int)rf_floor_float(v117) + 2;
  if ( v292 > 16 )
    v292 = 16;
  unk_8222C8 = v292;
  v309 = unk_82275C / (double)(v292 - 1);
  for ( i = 0; i < v286; ++i )
  {
    if ( i && i != v286 - 1 )
    {
      v54 = rf_random_float_range(-0.44999999, 0.44999999);
      v115 = v54 * v285;
      value = rf_vector_multiply_scalar(&flt_822730, v157, v115);
      v114 = (double)i * v285;
      v55 = rf_vector_multiply_scalar(&flt_822730, v159, v114);
      v56 = rf_vector_add(&flt_822724, v158, v55);
      v57 = rf_vector_add(v56, v156, value);
      rf_vector_copy(&unk_822768[80 * i], v155, v57);
    }
    else
    {
      v116 = (double)i * v285;
      v52 = rf_vector_multiply_scalar(&flt_822730, v162, v116);
      v53 = rf_vector_add(&flt_822724, v161, v52);
      rf_vector_copy(&unk_822768[80 * i], v160, v53);
    }
  }
  for ( j = 1; j < v292; ++j )
  {
    if ( i == 1 || i == v292 - 1 )
    {
      v113 = (double)j * v309;
      v58 = rf_vector_multiply_scalar(&flt_822750, v154, v113);
      v59 = rf_vector_add(&flt_822744, v153, v58);
      rf_vector_copy(&unk_822768[5 * j], v152, v59);
    }
    else
    {
      v60 = rf_random_float_range(-0.44999999, 0.44999999);
      v112 = v60 * v309;
      valuea = rf_vector_multiply_scalar(&flt_822750, v149, v112);
      v111 = (double)j * v309;
      v61 = rf_vector_multiply_scalar(&flt_822750, v151, v111);
      v62 = rf_vector_add(&flt_822744, v150, v61);
      v63 = rf_vector_add(v62, v148, valuea);
      rf_vector_copy(&unk_822768[5 * j], v147, v63);
    }
  }
  v285 = unk_823B98 / (double)(v286 - 1);
  for ( i = 1; i < v286; ++i )
  {
    if ( i == 1 || i == v286 - 1 )
    {
      v110 = (double)i * v285;
      v64 = rf_vector_multiply_scalar(&flt_823B8C, v146, v110);
      v65 = rf_vector_add(&flt_823B80, v145, v64);
      rf_vector_copy(&unk_822768[80 * i - 5 + 5 * v292], v144, v65);
    }
    else
    {
      v66 = rf_random_float_range(-0.44999999, 0.44999999);
      v109 = v66 * v285;
      valueb = rf_vector_multiply_scalar(&flt_823B8C, v141, v109);
      v108 = (double)i * v285;
      v67 = rf_vector_multiply_scalar(&flt_823B8C, v143, v108);
      v68 = rf_vector_add(&flt_823B80, v142, v67);
      v69 = rf_vector_add(v68, v140, valueb);
      rf_vector_copy(&unk_822768[80 * i - 5 + 5 * v292], v139, v69);
    }
  }
  v309 = unk_823BB8 / (double)(v292 - 1);
  for ( j = 1; j < v292 - 1; ++j )
  {
    if ( i == 1 || i == v292 - 2 )
    {
      v107 = (double)j * v309;
      v70 = rf_vector_multiply_scalar(&flt_823BAC, v138, v107);
      v71 = rf_vector_add(&flt_823BA0, v137, v70);
      rf_vector_copy(&unk_822768[80 * v286 - 80 + 5 * j], v136, v71);
    }
    else
    {
      v72 = rf_random_float_range(-0.44999999, 0.44999999);
      v106 = v72 * v309;
      valuec = rf_vector_multiply_scalar(&flt_823BAC, v133, v106);
      v105 = (double)j * v309;
      v73 = rf_vector_multiply_scalar(&flt_823BAC, v135, v105);
      v74 = rf_vector_add(&flt_823BA0, v134, v73);
      v75 = rf_vector_add(v74, v132, valuec);
      rf_vector_copy(&unk_822768[80 * v286 - 80 + 5 * j], v131, v75);
    }
  }
  rf_vector3_copy_return_destination(vector, &flt_823B8C);
  v285 = unk_823B98 / (double)(v286 - 1);
  rf_vector3_default_construct_noop(v293);
  for ( i = 1; i < v286 - 1; ++i )
  {
    v76 = rf_vector_subtract(&unk_822768[80 * i - 5 + 5 * v292], v130, &unk_822768[80 * i]);
    rf_vector_copy(v293, v129, v76);
    v77 = rf_vector3_length(v293);
    v309 = v77 / (double)(v292 - 1);
    rf_vector_normalize(v293);
    for ( j = 1; j < v292 - 1; ++j )
    {
      v78 = rf_random_float_range(-0.44999999, 0.44999999);
      v104 = v78 * v285;
      valued = rf_vector_multiply_scalar(vector, v124, v104);
      v79 = rf_random_float_range(-0.44999999, 0.44999999);
      v103 = v79 * v309;
      scalar = rf_vector_multiply_scalar(v293, v126, v103);
      v102 = (double)j * v309;
      v80 = rf_vector_multiply_scalar(v293, v128, v102);
      v81 = rf_vector_add(&unk_822768[80 * i], v127, v80);
      v82 = rf_vector_add(v81, v125, scalar);
      v83 = rf_vector_add(v82, v123, valued);
      rf_vector_copy(&unk_822768[80 * i + 5 * j], v122, v83);
    }
  }
  v295 = *(float *)(v305 + 4) - *(float *)(v301 + 4);
  v297 = *(float *)(v305 + 8) - *(float *)(v301 + 8);
  for ( i = 0; i < v286; ++i )
  {
    for ( j = 0; j < v292; ++j )
    {
      flt_82276C[80 * i + 2 + 5 * j] = v295 * unk_822768[80 * i + 5 * j] / unk_82273C + *(float *)(v301 + 4);
      flt_82276C[80 * i + 3 + 5 * j] = v297 * flt_82276C[80 * i + 5 * j] / unk_82275C + *(float *)(v301 + 8);
    }
  }
  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    for ( k = (float *)rf_glass_shard_bucket_heads[2 * i]; k; k = v101 )
    {
      if ( *((_DWORD *)k + 25) == *(_DWORD *)(a1 + 68) )
      {
        rf_random_unit_vector(k + 19);
        v84 = rf_random_float_range(3.1415927, 6.2831855);
        k[22] = v84;
        valuee = rf_random_float_range(3.0, 6.0);
        v85 = rf_floor_float(valuee);
        *((_DWORD *)k + 24) = (int)v85;
        k[25] = 0.0;
        if ( a3 )
          rf_glass_shard_launch_directional_delayed((int)k, a2, a3);
        else
          rf_glass_shard_launch_radial((int)k, a2, 0);
      }
      if ( *(_DWORD *)k == rf_glass_shard_bucket_heads[2 * i] )
        v101 = nullptr;
      else
        v101 = *(float **)k;
    }
  }
  v303 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(rf_world_solid + 156));
    if ( i >= first_dword )
      break;
    v278 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 156), i);
    for ( j = 0; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword((void *)(v278 + 108));
      if ( j >= first_dword )
        break;
      v277 = *(void **)sub_552200((_DWORD *)(v278 + 108), j);
      LOBYTE(first_dword) = (_BYTE)v277;
      if ( v277 == *(void **)(a1 + 68) && v277 != a4 )
      {
        v303 = 1;
        break;
      }
    }
    if ( v303 == 1 )
      break;
  }
  for ( i = 0; i < v286 - 1; ++i )
  {
    for ( j = 0; j < v292 - 1; ++j )
    {
      LOBYTE(first_dword) = rf_glass_shard_pool_allocate(&k, (int)a4);
      v276 = first_dword;
      if ( !k )
        return first_dword;
      k[49] = 0.0;
      rf_glass_shard_vertex_copy(k + 29, &unk_822768[80 * i + 5 * j]);
      rf_glass_shard_vertex_copy(k + 34, &unk_822768[80 * i + 5 + 5 * j]);
      rf_glass_shard_vertex_copy(k + 39, &unk_822768[80 * i + 85 + 5 * j]);
      rf_glass_shard_vertex_copy(k + 44, &unk_822768[80 * i + 80 + 5 * j]);
      rf_vector3_zero_return_destination(k + 2);
      for ( m = 0; m < 4; ++m )
        rf_vector_accumulate(k + 2, &k[5 * m + 29]);
      v87 = rf_vector_multiply_scalar(k + 2, v121, 0.25);
      rf_vector_copy(k + 2, v120, v87);
      rf_matrix3_copy(k + 5, destination);
      v275 = 0.0;
      v275 = rf_vector_fast_distance(k + 29, k + 2);
      v273 = rf_vector_fast_distance(k + 34, k + 2);
      if ( v275 < (double)v273 )
        v275 = v273;
      v273 = rf_vector_fast_distance(k + 39, k + 2);
      if ( v275 < (double)v273 )
        v275 = v273;
      v273 = rf_vector_fast_distance(k + 44, k + 2);
      if ( v275 < (double)v273 )
        v275 = v273;
      k[23] = v275;
      *((_DWORD *)k + 26) = a4;
      if ( v303 != 1
        || (v88 = rf_world_resolve_cached_room((void *)rf_world_solid, a4, scaled_result, k + 2, 0),
            (*((_DWORD *)k + 26) = v88) != 0) )
      {
        rf_glass_shard_room_bucket_link(k);
        for ( m = 0; m < 4; ++m )
          rf_vector_inverse_translate_rotate_in_place(&k[5 * m + 29], (int)(k + 2), (int)(k + 5));
        v89 = (float *)rf_rgba8_construct_components_return_self(v119, 255, 255, 255, 255);
        k[14] = *v89;
        rf_random_unit_vector(k + 19);
        v90 = rf_random_float_range(3.1415927, 6.2831855);
        k[22] = v90;
        valuef = rf_random_float_range(3.0, 6.0);
        v91 = rf_floor_float(valuef);
        *((_DWORD *)k + 24) = (int)v91;
        k[25] = 0.0;
        *((_DWORD *)k + 15) = rf_glass_blast_texture_handle;
        if ( a3 )
          rf_glass_shard_launch_directional_delayed((int)k, a2, a3);
        else
          rf_glass_shard_launch_radial((int)k, a2, 0);
      }
      else
      {
        rf_glass_shard_pool_release(k);
      }
    }
    LOBYTE(first_dword) = i + 1;
  }
  return first_dword;
}

