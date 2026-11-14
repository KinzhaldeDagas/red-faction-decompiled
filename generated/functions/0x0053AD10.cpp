// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053AD10 rf_geomod_embedded_cutter_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, embedded cutter literal geometry,all vertex/index/UV words and registry/procedural accessors,original ECX/stack flow and PE bytes): Cdecl name C string,caller pops4,returns newly constructed solid pointer orNULL for unmatched name. Four sequential case-insensitive FULL-name comparisons (no basename/extension stripping): Holey01.v3d=10vertices/16triangles,geometrySHA256 0d2c030252204a27d7b817a63e57140a08a0bf98c6d9fcfa178f7952ee7d3f66; bit_driller_double.v3d=34vertices/64triangles,geometrySHA256 b8f8c59663c062f1f1f0b02fbd84117d52ca84aed4ef1284443be910fa26ee17; bit_driller_single.v3d=15vertices/26triangles,geometrySHA256 b0fa616e1825a563176d2cb417e81d1ffa88578b50e87b75bb45fa8bed986466; Holey_APC.v3d=34vertices/64triangles,geometrySHA256 3d14477e57680c843f79734f027800eca18d027a3d797bebb23c983ffcb29a16. Counts/entire
// ordered geometry independently reconstructed from native FLD/FLDZ constants,stack flow and index immediates and compared bit-for-bit with fresh pseudocode. Geometry SHA packs all ordered xyz binary32 words, then for each ordered corner uint32 vertexIndex plus four attribute words, little-endian. Exact positions and triangle indices/UV bits are saved as93 vertex-call and170 face-allocation instruction annotations. Each branch allocates888-byte solid, appends EACH literal vertex as distinct44-byte record (no dedup/scale), initializes24-byte metadata then sets metadataDWORD8=-1,allocates/links triangles in literal order and appends three corners sharing indexed vertices with literal primaryUV and zero secondaryUV. UVs are per-corner and can differ for shared vertices; no UV wrapping. Rebuild solid bounds/sphere BEFORE creating one460-byte room using solid bounds72/84. Iterate all solid
// faces in order, call finalize(face,NULL,0), IGNORE return, attach each to room, then rebuild room spatial tree; returnsolid regardless of finalizer statuses. Constructor registers room in both solid arrays144/156. No filesystem/mesh parser,source recentering,Boolean operation,geometry transform or material resolution in this body. Solid/room allocation NULL branches exist but subsequent use is unguarded; no reliable allocation-failure fallback or transactional rollback. GS checks/SEH cleanup are compiler scaffolding. Caller44A460 separately caches results by name.
_DWORD *__cdecl rf_geomod_embedded_cutter_create(char *String1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  int *v11; // eax
  int *v12; // eax
  int *v13; // eax
  int *v14; // eax
  int *v15; // eax
  int *v16; // eax
  int *v17; // eax
  int *v18; // eax
  int *v19; // eax
  int *v20; // eax
  int *v21; // eax
  int *v22; // eax
  int *v23; // eax
  int *v24; // eax
  int *v25; // eax
  int *v26; // eax
  int *v27; // eax
  int *v28; // eax
  int *v29; // eax
  int *v30; // eax
  int *v31; // eax
  int *v32; // eax
  int *v33; // eax
  int *v34; // eax
  int *v35; // eax
  int *v36; // eax
  int *v37; // eax
  int *v38; // eax
  int *v39; // eax
  int *v40; // eax
  int *v41; // eax
  int *v42; // eax
  int *v43; // eax
  int *v44; // eax
  int *v45; // eax
  int *v46; // eax
  int *v47; // eax
  int *v48; // eax
  int *v49; // eax
  int *v50; // eax
  int *v51; // eax
  int *v52; // eax
  int *v53; // eax
  int *v54; // eax
  int *v55; // eax
  int *v56; // eax
  int *v57; // eax
  int *v58; // eax
  float *v60; // eax
  float *v61; // eax
  float *v62; // eax
  float *v63; // eax
  float *v64; // eax
  float *v65; // eax
  float *v66; // eax
  float *v67; // eax
  float *v68; // eax
  float *v69; // eax
  float *v70; // eax
  float *v71; // eax
  float *v72; // eax
  float *v73; // eax
  float *v74; // eax
  float *v75; // eax
  float *v76; // eax
  float *v77; // eax
  float *v78; // eax
  float *v79; // eax
  float *v80; // eax
  float *v81; // eax
  float *v82; // eax
  float *v83; // eax
  float *v84; // eax
  float *v85; // eax
  float *v86; // eax
  float *v87; // eax
  float *v88; // eax
  float *v89; // eax
  float *v90; // eax
  float *v91; // eax
  float *v92; // eax
  float *v93; // eax
  int *v94; // eax
  int *v95; // eax
  int *v96; // eax
  int *v97; // eax
  int *v98; // eax
  int *v99; // eax
  int *v100; // eax
  int *v101; // eax
  int *v102; // eax
  int *v103; // eax
  int *v104; // eax
  int *v105; // eax
  int *v106; // eax
  int *v107; // eax
  int *v108; // eax
  int *v109; // eax
  int *v110; // eax
  int *v111; // eax
  int *v112; // eax
  int *v113; // eax
  int *v114; // eax
  int *v115; // eax
  int *v116; // eax
  int *v117; // eax
  int *v118; // eax
  int *v119; // eax
  int *v120; // eax
  int *v121; // eax
  int *v122; // eax
  int *v123; // eax
  int *v124; // eax
  int *v125; // eax
  int *v126; // eax
  int *v127; // eax
  int *v128; // eax
  int *v129; // eax
  int *v130; // eax
  int *v131; // eax
  int *v132; // eax
  int *v133; // eax
  int *v134; // eax
  int *v135; // eax
  int *v136; // eax
  int *v137; // eax
  int *v138; // eax
  int *v139; // eax
  int *v140; // eax
  int *v141; // eax
  int *v142; // eax
  int *v143; // eax
  int *v144; // eax
  int *v145; // eax
  int *v146; // eax
  int *v147; // eax
  int *v148; // eax
  int *v149; // eax
  int *v150; // eax
  int *v151; // eax
  int *v152; // eax
  int *v153; // eax
  int *v154; // eax
  int *v155; // eax
  int *v156; // eax
  int *v157; // eax
  int *v158; // eax
  int *v159; // eax
  int *v160; // eax
  int *v161; // eax
  int *v162; // eax
  int *v163; // eax
  int *v164; // eax
  int *v165; // eax
  int *v166; // eax
  int *v167; // eax
  int *v168; // eax
  int *v169; // eax
  int *v170; // eax
  int *v171; // eax
  int *v172; // eax
  int *v173; // eax
  int *v174; // eax
  int *v175; // eax
  int *v176; // eax
  int *v177; // eax
  int *v178; // eax
  int *v179; // eax
  int *v180; // eax
  int *v181; // eax
  int *v182; // eax
  int *v183; // eax
  int *v184; // eax
  int *v185; // eax
  int *v186; // eax
  int *v187; // eax
  int *v188; // eax
  int *v189; // eax
  int *v190; // eax
  int *v191; // eax
  int *v192; // eax
  int *v193; // eax
  int *v194; // eax
  int *v195; // eax
  int *v196; // eax
  int *v197; // eax
  int *v198; // eax
  int *v199; // eax
  int *v200; // eax
  int *v201; // eax
  int *v202; // eax
  int *v203; // eax
  int *v204; // eax
  int *v205; // eax
  int *v206; // eax
  int *v207; // eax
  int *v208; // eax
  int *v209; // eax
  int *v210; // eax
  int *v211; // eax
  int *v212; // eax
  int *v213; // eax
  int *v214; // eax
  int *v215; // eax
  int *v216; // eax
  int *v217; // eax
  int *v218; // eax
  int *v219; // eax
  int *v220; // eax
  int *v221; // eax
  int *v222; // eax
  int *v223; // eax
  int *v224; // eax
  int *v225; // eax
  int *v226; // eax
  int *v227; // eax
  int *v228; // eax
  int *v229; // eax
  int *v230; // eax
  int *v231; // eax
  int *v232; // eax
  int *v233; // eax
  int *v234; // eax
  int *v235; // eax
  int *v236; // eax
  int *v237; // eax
  int *v238; // eax
  int *v239; // eax
  int *v240; // eax
  int *v241; // eax
  int *v242; // eax
  int *v243; // eax
  int *v244; // eax
  int *v245; // eax
  int *v246; // eax
  int *v247; // eax
  int *v248; // eax
  int *v249; // eax
  int *v250; // eax
  int *v251; // eax
  int *v252; // eax
  int *v253; // eax
  int *v254; // eax
  int *v255; // eax
  int *v256; // eax
  int *v257; // eax
  int *v258; // eax
  int *v259; // eax
  int *v260; // eax
  int *v261; // eax
  int *v262; // eax
  int *v263; // eax
  int *v264; // eax
  int *v265; // eax
  int *v266; // eax
  int *v267; // eax
  int *v268; // eax
  int *v269; // eax
  int *v270; // eax
  int *v271; // eax
  int *v272; // eax
  int *v273; // eax
  int *v274; // eax
  int *v275; // eax
  int *v276; // eax
  int *v277; // eax
  int *v278; // eax
  int *v279; // eax
  int *v280; // eax
  int *v281; // eax
  int *v282; // eax
  int *v283; // eax
  int *v284; // eax
  int *v285; // eax
  float *v286; // eax
  float *v287; // eax
  float *v288; // eax
  float *v289; // eax
  float *v290; // eax
  float *v291; // eax
  float *v292; // eax
  float *v293; // eax
  float *v294; // eax
  float *v295; // eax
  float *v296; // eax
  float *v297; // eax
  float *v298; // eax
  float *v299; // eax
  float *v300; // eax
  int *v301; // eax
  int *v302; // eax
  int *v303; // eax
  int *v304; // eax
  int *v305; // eax
  int *v306; // eax
  int *v307; // eax
  int *v308; // eax
  int *v309; // eax
  int *v310; // eax
  int *v311; // eax
  int *v312; // eax
  int *v313; // eax
  int *v314; // eax
  int *v315; // eax
  int *v316; // eax
  int *v317; // eax
  int *v318; // eax
  int *v319; // eax
  int *v320; // eax
  int *v321; // eax
  int *v322; // eax
  int *v323; // eax
  int *v324; // eax
  int *v325; // eax
  int *v326; // eax
  int *v327; // eax
  int *v328; // eax
  int *v329; // eax
  int *v330; // eax
  int *v331; // eax
  int *v332; // eax
  int *v333; // eax
  int *v334; // eax
  int *v335; // eax
  int *v336; // eax
  int *v337; // eax
  int *v338; // eax
  int *v339; // eax
  int *v340; // eax
  int *v341; // eax
  int *v342; // eax
  int *v343; // eax
  int *v344; // eax
  int *v345; // eax
  int *v346; // eax
  int *v347; // eax
  int *v348; // eax
  int *v349; // eax
  int *v350; // eax
  int *v351; // eax
  int *v352; // eax
  int *v353; // eax
  int *v354; // eax
  int *v355; // eax
  int *v356; // eax
  int *v357; // eax
  int *v358; // eax
  int *v359; // eax
  int *v360; // eax
  int *v361; // eax
  int *v362; // eax
  int *v363; // eax
  int *v364; // eax
  int *v365; // eax
  int *v366; // eax
  int *v367; // eax
  int *v368; // eax
  int *v369; // eax
  int *v370; // eax
  int *v371; // eax
  int *v372; // eax
  int *v373; // eax
  int *v374; // eax
  int *v375; // eax
  int *v376; // eax
  int *v377; // eax
  int *v378; // eax
  float *v379; // eax
  float *v380; // eax
  float *v381; // eax
  float *v382; // eax
  float *v383; // eax
  float *v384; // eax
  float *v385; // eax
  float *v386; // eax
  float *v387; // eax
  float *v388; // eax
  float *v389; // eax
  float *v390; // eax
  float *v391; // eax
  float *v392; // eax
  float *v393; // eax
  float *v394; // eax
  float *v395; // eax
  float *v396; // eax
  float *v397; // eax
  float *v398; // eax
  float *v399; // eax
  float *v400; // eax
  float *v401; // eax
  float *v402; // eax
  float *v403; // eax
  float *v404; // eax
  float *v405; // eax
  float *v406; // eax
  float *v407; // eax
  float *v408; // eax
  float *v409; // eax
  float *v410; // eax
  float *v411; // eax
  float *v412; // eax
  int *v413; // eax
  int *v414; // eax
  int *v415; // eax
  int *v416; // eax
  int *v417; // eax
  int *v418; // eax
  int *v419; // eax
  int *v420; // eax
  int *v421; // eax
  int *v422; // eax
  int *v423; // eax
  int *v424; // eax
  int *v425; // eax
  int *v426; // eax
  int *v427; // eax
  int *v428; // eax
  int *v429; // eax
  int *v430; // eax
  int *v431; // eax
  int *v432; // eax
  int *v433; // eax
  int *v434; // eax
  int *v435; // eax
  int *v436; // eax
  int *v437; // eax
  int *v438; // eax
  int *v439; // eax
  int *v440; // eax
  int *v441; // eax
  int *v442; // eax
  int *v443; // eax
  int *v444; // eax
  int *v445; // eax
  int *v446; // eax
  int *v447; // eax
  int *v448; // eax
  int *v449; // eax
  int *v450; // eax
  int *v451; // eax
  int *v452; // eax
  int *v453; // eax
  int *v454; // eax
  int *v455; // eax
  int *v456; // eax
  int *v457; // eax
  int *v458; // eax
  int *v459; // eax
  int *v460; // eax
  int *v461; // eax
  int *v462; // eax
  int *v463; // eax
  int *v464; // eax
  int *v465; // eax
  int *v466; // eax
  int *v467; // eax
  int *v468; // eax
  int *v469; // eax
  int *v470; // eax
  int *v471; // eax
  int *v472; // eax
  int *v473; // eax
  int *v474; // eax
  int *v475; // eax
  int *v476; // eax
  int *v477; // eax
  int *v478; // eax
  int *v479; // eax
  int *v480; // eax
  int *v481; // eax
  int *v482; // eax
  int *v483; // eax
  int *v484; // eax
  int *v485; // eax
  int *v486; // eax
  int *v487; // eax
  int *v488; // eax
  int *v489; // eax
  int *v490; // eax
  int *v491; // eax
  int *v492; // eax
  int *v493; // eax
  int *v494; // eax
  int *v495; // eax
  int *v496; // eax
  int *v497; // eax
  int *v498; // eax
  int *v499; // eax
  int *v500; // eax
  int *v501; // eax
  int *v502; // eax
  int *v503; // eax
  int *v504; // eax
  int *v505; // eax
  int *v506; // eax
  int *v507; // eax
  int *v508; // eax
  int *v509; // eax
  int *v510; // eax
  int *v511; // eax
  int *v512; // eax
  int *v513; // eax
  int *v514; // eax
  int *v515; // eax
  int *v516; // eax
  int *v517; // eax
  int *v518; // eax
  int *v519; // eax
  int *v520; // eax
  int *v521; // eax
  int *v522; // eax
  int *v523; // eax
  int *v524; // eax
  int *v525; // eax
  int *v526; // eax
  int *v527; // eax
  int *v528; // eax
  int *v529; // eax
  int *v530; // eax
  int *v531; // eax
  int *v532; // eax
  int *v533; // eax
  int *v534; // eax
  int *v535; // eax
  int *v536; // eax
  int *v537; // eax
  int *v538; // eax
  int *v539; // eax
  int *v540; // eax
  int *v541; // eax
  int *v542; // eax
  int *v543; // eax
  int *v544; // eax
  int *v545; // eax
  int *v546; // eax
  int *v547; // eax
  int *v548; // eax
  int *v549; // eax
  int *v550; // eax
  int *v551; // eax
  int *v552; // eax
  int *v553; // eax
  int *v554; // eax
  int *v555; // eax
  int *v556; // eax
  int *v557; // eax
  int *v558; // eax
  int *v559; // eax
  int *v560; // eax
  int *v561; // eax
  int *v562; // eax
  int *v563; // eax
  int *v564; // eax
  int *v565; // eax
  int *v566; // eax
  int *v567; // eax
  int *v568; // eax
  int *v569; // eax
  int *v570; // eax
  int *v571; // eax
  int *v572; // eax
  int *v573; // eax
  int *v574; // eax
  int *v575; // eax
  int *v576; // eax
  int *v577; // eax
  int *v578; // eax
  int *v579; // eax
  int *v580; // eax
  int *v581; // eax
  int *v582; // eax
  int *v583; // eax
  int *v584; // eax
  int *v585; // eax
  int *v586; // eax
  int *v587; // eax
  int *v588; // eax
  int *v589; // eax
  int *v590; // eax
  int *v591; // eax
  int *v592; // eax
  int *v593; // eax
  int *v594; // eax
  int *v595; // eax
  int *v596; // eax
  int *v597; // eax
  int *v598; // eax
  int *v599; // eax
  int *v600; // eax
  int *v601; // eax
  int *v602; // eax
  int *v603; // eax
  int *v604; // eax
  int *v605; // [esp+1Ch] [ebp-A34h]
  void **v606; // [esp+20h] [ebp-A30h]
  int *v607; // [esp+24h] [ebp-A2Ch]
  void **v608; // [esp+28h] [ebp-A28h]
  int *v609; // [esp+2Ch] [ebp-A24h]
  void **v610; // [esp+30h] [ebp-A20h]
  int *v611; // [esp+34h] [ebp-A1Ch]
  void **v612; // [esp+38h] [ebp-A18h]
  void *v613; // [esp+3Ch] [ebp-A14h]
  float v614[3]; // [esp+44h] [ebp-A0Ch] BYREF
  float v615[3]; // [esp+50h] [ebp-A00h] BYREF
  float v616[3]; // [esp+5Ch] [ebp-9F4h] BYREF
  float v617[3]; // [esp+68h] [ebp-9E8h] BYREF
  float v618[3]; // [esp+74h] [ebp-9DCh] BYREF
  float v619[3]; // [esp+80h] [ebp-9D0h] BYREF
  float v620[3]; // [esp+8Ch] [ebp-9C4h] BYREF
  float v621[3]; // [esp+98h] [ebp-9B8h] BYREF
  float v622[3]; // [esp+A4h] [ebp-9ACh] BYREF
  float v623[3]; // [esp+B0h] [ebp-9A0h] BYREF
  float v624[3]; // [esp+BCh] [ebp-994h] BYREF
  float v625[3]; // [esp+C8h] [ebp-988h] BYREF
  float v626[3]; // [esp+D4h] [ebp-97Ch] BYREF
  float v627[3]; // [esp+E0h] [ebp-970h] BYREF
  float v628[3]; // [esp+ECh] [ebp-964h] BYREF
  float v629[3]; // [esp+F8h] [ebp-958h] BYREF
  float v630[3]; // [esp+104h] [ebp-94Ch] BYREF
  float v631[3]; // [esp+110h] [ebp-940h] BYREF
  float v632[3]; // [esp+11Ch] [ebp-934h] BYREF
  float v633[3]; // [esp+128h] [ebp-928h] BYREF
  float v634[3]; // [esp+134h] [ebp-91Ch] BYREF
  float v635[3]; // [esp+140h] [ebp-910h] BYREF
  float v636[3]; // [esp+14Ch] [ebp-904h] BYREF
  float v637[3]; // [esp+158h] [ebp-8F8h] BYREF
  float v638[3]; // [esp+164h] [ebp-8ECh] BYREF
  float v639[3]; // [esp+170h] [ebp-8E0h] BYREF
  float v640[3]; // [esp+17Ch] [ebp-8D4h] BYREF
  float v641[3]; // [esp+188h] [ebp-8C8h] BYREF
  float v642[3]; // [esp+194h] [ebp-8BCh] BYREF
  float v643[3]; // [esp+1A0h] [ebp-8B0h] BYREF
  float v644[3]; // [esp+1ACh] [ebp-8A4h] BYREF
  float v645[3]; // [esp+1B8h] [ebp-898h] BYREF
  float v646[3]; // [esp+1C4h] [ebp-88Ch] BYREF
  float v647[3]; // [esp+1D0h] [ebp-880h] BYREF
  float v648[3]; // [esp+1DCh] [ebp-874h] BYREF
  float v649[3]; // [esp+1E8h] [ebp-868h] BYREF
  float v650[3]; // [esp+1F4h] [ebp-85Ch] BYREF
  float v651[3]; // [esp+200h] [ebp-850h] BYREF
  float v652[3]; // [esp+20Ch] [ebp-844h] BYREF
  float v653[3]; // [esp+218h] [ebp-838h] BYREF
  float v654[3]; // [esp+224h] [ebp-82Ch] BYREF
  float v655[3]; // [esp+230h] [ebp-820h] BYREF
  float v656[3]; // [esp+23Ch] [ebp-814h] BYREF
  float v657[3]; // [esp+248h] [ebp-808h] BYREF
  float v658[3]; // [esp+254h] [ebp-7FCh] BYREF
  float v659[3]; // [esp+260h] [ebp-7F0h] BYREF
  float v660[3]; // [esp+26Ch] [ebp-7E4h] BYREF
  float v661[3]; // [esp+278h] [ebp-7D8h] BYREF
  float v662[3]; // [esp+284h] [ebp-7CCh] BYREF
  float v663[3]; // [esp+290h] [ebp-7C0h] BYREF
  float v664[3]; // [esp+29Ch] [ebp-7B4h] BYREF
  float v665[3]; // [esp+2A8h] [ebp-7A8h] BYREF
  float v666[3]; // [esp+2B4h] [ebp-79Ch] BYREF
  float v667[3]; // [esp+2C0h] [ebp-790h] BYREF
  float v668[3]; // [esp+2CCh] [ebp-784h] BYREF
  float v669[3]; // [esp+2D8h] [ebp-778h] BYREF
  float v670[3]; // [esp+2E4h] [ebp-76Ch] BYREF
  float v671[3]; // [esp+2F0h] [ebp-760h] BYREF
  float v672[3]; // [esp+2FCh] [ebp-754h] BYREF
  float v673[3]; // [esp+308h] [ebp-748h] BYREF
  float v674[3]; // [esp+314h] [ebp-73Ch] BYREF
  float v675[3]; // [esp+320h] [ebp-730h] BYREF
  float v676[3]; // [esp+32Ch] [ebp-724h] BYREF
  float v677[3]; // [esp+338h] [ebp-718h] BYREF
  float v678[3]; // [esp+344h] [ebp-70Ch] BYREF
  float v679[3]; // [esp+350h] [ebp-700h] BYREF
  float v680[3]; // [esp+35Ch] [ebp-6F4h] BYREF
  float v681[3]; // [esp+368h] [ebp-6E8h] BYREF
  void *v682; // [esp+374h] [ebp-6DCh]
  void **v683; // [esp+378h] [ebp-6D8h]
  void *v684; // [esp+37Ch] [ebp-6D4h]
  int *v685; // [esp+380h] [ebp-6D0h]
  float v686[3]; // [esp+384h] [ebp-6CCh] BYREF
  float v687[3]; // [esp+390h] [ebp-6C0h] BYREF
  float v688[3]; // [esp+39Ch] [ebp-6B4h] BYREF
  float v689[3]; // [esp+3A8h] [ebp-6A8h] BYREF
  float v690[3]; // [esp+3B4h] [ebp-69Ch] BYREF
  float v691[3]; // [esp+3C0h] [ebp-690h] BYREF
  float v692[3]; // [esp+3CCh] [ebp-684h] BYREF
  float v693[3]; // [esp+3D8h] [ebp-678h] BYREF
  float v694[3]; // [esp+3E4h] [ebp-66Ch] BYREF
  float v695[3]; // [esp+3F0h] [ebp-660h] BYREF
  float v696[3]; // [esp+3FCh] [ebp-654h] BYREF
  float v697[3]; // [esp+408h] [ebp-648h] BYREF
  float v698[3]; // [esp+414h] [ebp-63Ch] BYREF
  float v699[3]; // [esp+420h] [ebp-630h] BYREF
  float v700[3]; // [esp+42Ch] [ebp-624h] BYREF
  float v701[3]; // [esp+438h] [ebp-618h] BYREF
  float v702[3]; // [esp+444h] [ebp-60Ch] BYREF
  float v703[3]; // [esp+450h] [ebp-600h] BYREF
  float v704[3]; // [esp+45Ch] [ebp-5F4h] BYREF
  float v705[3]; // [esp+468h] [ebp-5E8h] BYREF
  float v706[3]; // [esp+474h] [ebp-5DCh] BYREF
  float v707[3]; // [esp+480h] [ebp-5D0h] BYREF
  float v708[3]; // [esp+48Ch] [ebp-5C4h] BYREF
  float v709[3]; // [esp+498h] [ebp-5B8h] BYREF
  float v710[3]; // [esp+4A4h] [ebp-5ACh] BYREF
  float v711[3]; // [esp+4B0h] [ebp-5A0h] BYREF
  float v712[3]; // [esp+4BCh] [ebp-594h] BYREF
  float v713[3]; // [esp+4C8h] [ebp-588h] BYREF
  float v714[3]; // [esp+4D4h] [ebp-57Ch] BYREF
  float v715[3]; // [esp+4E0h] [ebp-570h] BYREF
  void *v716; // [esp+4ECh] [ebp-564h]
  void **v717; // [esp+4F0h] [ebp-560h]
  void *v718; // [esp+4F4h] [ebp-55Ch]
  int *v719; // [esp+4F8h] [ebp-558h]
  float v720[3]; // [esp+4FCh] [ebp-554h] BYREF
  float v721[3]; // [esp+508h] [ebp-548h] BYREF
  float v722[3]; // [esp+514h] [ebp-53Ch] BYREF
  float v723[3]; // [esp+520h] [ebp-530h] BYREF
  float v724[3]; // [esp+52Ch] [ebp-524h] BYREF
  float v725[3]; // [esp+538h] [ebp-518h] BYREF
  float v726[3]; // [esp+544h] [ebp-50Ch] BYREF
  float v727[3]; // [esp+550h] [ebp-500h] BYREF
  float v728[3]; // [esp+55Ch] [ebp-4F4h] BYREF
  float v729[3]; // [esp+568h] [ebp-4E8h] BYREF
  float v730[3]; // [esp+574h] [ebp-4DCh] BYREF
  float v731[3]; // [esp+580h] [ebp-4D0h] BYREF
  float v732[3]; // [esp+58Ch] [ebp-4C4h] BYREF
  float v733[3]; // [esp+598h] [ebp-4B8h] BYREF
  float v734[3]; // [esp+5A4h] [ebp-4ACh] BYREF
  float v735[3]; // [esp+5B0h] [ebp-4A0h] BYREF
  float v736[3]; // [esp+5BCh] [ebp-494h] BYREF
  float v737[3]; // [esp+5C8h] [ebp-488h] BYREF
  float v738[3]; // [esp+5D4h] [ebp-47Ch] BYREF
  float v739[3]; // [esp+5E0h] [ebp-470h] BYREF
  float v740[3]; // [esp+5ECh] [ebp-464h] BYREF
  float v741[3]; // [esp+5F8h] [ebp-458h] BYREF
  float v742[3]; // [esp+604h] [ebp-44Ch] BYREF
  float v743[3]; // [esp+610h] [ebp-440h] BYREF
  float v744[3]; // [esp+61Ch] [ebp-434h] BYREF
  float v745[3]; // [esp+628h] [ebp-428h] BYREF
  float v746[3]; // [esp+634h] [ebp-41Ch] BYREF
  float v747[3]; // [esp+640h] [ebp-410h] BYREF
  float v748[3]; // [esp+64Ch] [ebp-404h] BYREF
  float v749[3]; // [esp+658h] [ebp-3F8h] BYREF
  float v750[3]; // [esp+664h] [ebp-3ECh] BYREF
  float v751[3]; // [esp+670h] [ebp-3E0h] BYREF
  float v752[3]; // [esp+67Ch] [ebp-3D4h] BYREF
  float v753[3]; // [esp+688h] [ebp-3C8h] BYREF
  float v754[3]; // [esp+694h] [ebp-3BCh] BYREF
  float v755[3]; // [esp+6A0h] [ebp-3B0h] BYREF
  float v756[3]; // [esp+6ACh] [ebp-3A4h] BYREF
  float v757[3]; // [esp+6B8h] [ebp-398h] BYREF
  float v758[3]; // [esp+6C4h] [ebp-38Ch] BYREF
  float v759[3]; // [esp+6D0h] [ebp-380h] BYREF
  float v760[3]; // [esp+6DCh] [ebp-374h] BYREF
  float v761[3]; // [esp+6E8h] [ebp-368h] BYREF
  float v762[3]; // [esp+6F4h] [ebp-35Ch] BYREF
  float v763[3]; // [esp+700h] [ebp-350h] BYREF
  float v764[3]; // [esp+70Ch] [ebp-344h] BYREF
  float v765[3]; // [esp+718h] [ebp-338h] BYREF
  float v766[3]; // [esp+724h] [ebp-32Ch] BYREF
  float v767[3]; // [esp+730h] [ebp-320h] BYREF
  float v768[3]; // [esp+73Ch] [ebp-314h] BYREF
  float v769[3]; // [esp+748h] [ebp-308h] BYREF
  float v770[3]; // [esp+754h] [ebp-2FCh] BYREF
  float v771[3]; // [esp+760h] [ebp-2F0h] BYREF
  float v772[3]; // [esp+76Ch] [ebp-2E4h] BYREF
  float v773[3]; // [esp+778h] [ebp-2D8h] BYREF
  float v774[3]; // [esp+784h] [ebp-2CCh] BYREF
  float v775[3]; // [esp+790h] [ebp-2C0h] BYREF
  float v776[3]; // [esp+79Ch] [ebp-2B4h] BYREF
  float v777[3]; // [esp+7A8h] [ebp-2A8h] BYREF
  float v778[3]; // [esp+7B4h] [ebp-29Ch] BYREF
  float v779[3]; // [esp+7C0h] [ebp-290h] BYREF
  float v780[3]; // [esp+7CCh] [ebp-284h] BYREF
  float v781[3]; // [esp+7D8h] [ebp-278h] BYREF
  float v782[3]; // [esp+7E4h] [ebp-26Ch] BYREF
  float v783[3]; // [esp+7F0h] [ebp-260h] BYREF
  float v784[3]; // [esp+7FCh] [ebp-254h] BYREF
  float v785[3]; // [esp+808h] [ebp-248h] BYREF
  float v786[3]; // [esp+814h] [ebp-23Ch] BYREF
  float v787[3]; // [esp+820h] [ebp-230h] BYREF
  void *v788; // [esp+82Ch] [ebp-224h]
  void **v789; // [esp+830h] [ebp-220h]
  void *room; // [esp+834h] [ebp-21Ch]
  int *v791; // [esp+838h] [ebp-218h]
  float v792[3]; // [esp+83Ch] [ebp-214h] BYREF
  float v793[3]; // [esp+848h] [ebp-208h] BYREF
  float v794[3]; // [esp+854h] [ebp-1FCh] BYREF
  float v795[3]; // [esp+860h] [ebp-1F0h] BYREF
  float v796[3]; // [esp+86Ch] [ebp-1E4h] BYREF
  float v797[3]; // [esp+878h] [ebp-1D8h] BYREF
  float v798[3]; // [esp+884h] [ebp-1CCh] BYREF
  float v799[3]; // [esp+890h] [ebp-1C0h] BYREF
  float v800[3]; // [esp+89Ch] [ebp-1B4h] BYREF
  float v801[3]; // [esp+8A8h] [ebp-1A8h] BYREF
  float v802[3]; // [esp+8B4h] [ebp-19Ch] BYREF
  float v803[3]; // [esp+8C0h] [ebp-190h] BYREF
  float v804[3]; // [esp+8CCh] [ebp-184h] BYREF
  float v805[3]; // [esp+8D8h] [ebp-178h] BYREF
  float v806[3]; // [esp+8E4h] [ebp-16Ch] BYREF
  float v807[3]; // [esp+8F0h] [ebp-160h] BYREF
  float v808[3]; // [esp+8FCh] [ebp-154h] BYREF
  float v809[3]; // [esp+908h] [ebp-148h] BYREF
  float copy_result[3]; // [esp+914h] [ebp-13Ch] BYREF
  float v811[3]; // [esp+920h] [ebp-130h] BYREF
  void *v812; // [esp+92Ch] [ebp-124h]
  void **v813; // [esp+930h] [ebp-120h]
  char v814[16]; // [esp+934h] [ebp-11Ch] BYREF
  float *v815; // [esp+944h] [ebp-10Ch]
  float *k; // [esp+948h] [ebp-108h]
  float v817[3]; // [esp+94Ch] [ebp-104h] BYREF
  void *v818; // [esp+958h] [ebp-F8h]
  unsigned int v819[6]; // [esp+95Ch] [ebp-F4h] BYREF
  char v820[24]; // [esp+974h] [ebp-DCh] BYREF
  float *v821; // [esp+98Ch] [ebp-C4h]
  float *j; // [esp+990h] [ebp-C0h]
  float v823[3]; // [esp+994h] [ebp-BCh] BYREF
  void *v824; // [esp+9A0h] [ebp-B0h]
  unsigned int v825[6]; // [esp+9A4h] [ebp-ACh] BYREF
  char v826[24]; // [esp+9BCh] [ebp-94h] BYREF
  float *v827; // [esp+9D4h] [ebp-7Ch]
  float *i; // [esp+9D8h] [ebp-78h]
  float v829[3]; // [esp+9DCh] [ebp-74h] BYREF
  void *v830; // [esp+9E8h] [ebp-68h]
  unsigned int v831[6]; // [esp+9ECh] [ebp-64h] BYREF
  _DWORD v832[3]; // [esp+A04h] [ebp-4Ch] BYREF
  float *v833; // [esp+A14h] [ebp-3Ch]
  float *link; // [esp+A18h] [ebp-38h]
  float destination[3]; // [esp+A1Ch] [ebp-34h] BYREF
  void *solid; // [esp+A28h] [ebp-28h]
  unsigned int metadata[6]; // [esp+A2Ch] [ebp-24h] BYREF
  int v838; // [esp+A4Ch] [ebp-4h]

  if ( !_stricmp(String1, "Holey01.v3d") )
  {
    qmemcpy(v832, "Holey01.", 8);
    v832[2] = "box";
    v812 = operator new(0x378u);
    v838 = 0;
    if ( v812 )
      v612 = rf_solid888_construct((void **)v812);
    else
      v612 = nullptr;
    v813 = v612;
    v838 = -1;
    solid = v612;
    rf_vector3_default_construct_noop(destination);
    v1 = rf_vector3_set_components_return_destination(v811, -0.047975, 0.16412, -0.043788001);
    rf_vector_copy(destination, copy_result, v1);
    rf_solid_vertex_copy_append(solid, destination);
    v2 = rf_vector3_set_components_return_destination(v809, 0.134831, 0.123926, -0.023879999);
    rf_vector_copy(destination, v808, v2);
    rf_solid_vertex_copy_append(solid, destination);
    v3 = rf_vector3_set_components_return_destination(v807, 0.011597, 0.152806, 0.094286002);
    rf_vector_copy(destination, v806, v3);
    rf_solid_vertex_copy_append(solid, destination);
    v4 = rf_vector3_set_components_return_destination(v805, 0.125826, -0.139799, 0.02991);
    rf_vector_copy(destination, v804, v4);
    rf_solid_vertex_copy_append(solid, destination);
    v5 = rf_vector3_set_components_return_destination(v803, 0.093312003, -0.065722004, -0.147668);
    rf_vector_copy(destination, v802, v5);
    rf_solid_vertex_copy_append(solid, destination);
    v6 = rf_vector3_set_components_return_destination(v801, 0.114348, -0.022375001, 0.147668);
    rf_vector_copy(destination, v800, v6);
    rf_solid_vertex_copy_append(solid, destination);
    v7 = rf_vector3_set_components_return_destination(v799, -0.134831, 0.085574001, 0.072916999);
    rf_vector_copy(destination, v798, v7);
    rf_solid_vertex_copy_append(solid, destination);
    v8 = rf_vector3_set_components_return_destination(v797, -0.120187, 0.028455, -0.125824);
    rf_vector_copy(destination, v796, v8);
    rf_solid_vertex_copy_append(solid, destination);
    v9 = rf_vector3_set_components_return_destination(v795, 0.0048469999, -0.16412, -0.086970001);
    rf_vector_copy(destination, v794, v9);
    rf_solid_vertex_copy_append(solid, destination);
    v10 = rf_vector3_set_components_return_destination(v793, -0.066091001, -0.15276401, 0.077872001);
    rf_vector_copy(destination, v792, v10);
    rf_solid_vertex_copy_append(solid, destination);
    rf_geomod_face_metadata_init(metadata);
    metadata[2] = -1;
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v11 = (int *)sub_552200((_DWORD *)solid + 30, 0);
    rf_geomod_face_corner_append(link, *v11, 0.80161399, 0.67993402, 0.0, 0.0);
    v12 = (int *)sub_552200((_DWORD *)solid + 30, 1);
    rf_geomod_face_corner_append(link, *v12, 1.3331521, 0.898781, 0.0, 0.0);
    v13 = (int *)sub_552200((_DWORD *)solid + 30, 2);
    rf_geomod_face_corner_append(link, *v13, 1.720782, 0.76556998, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v14 = (int *)sub_552200((_DWORD *)solid + 30, 3);
    rf_geomod_face_corner_append(link, *v14, 0.43071499, 1.6435601, 0.0, 0.0);
    v15 = (int *)sub_552200((_DWORD *)solid + 30, 1);
    rf_geomod_face_corner_append(link, *v15, 0.333152, 0.898781, 0.0, 0.0);
    v16 = (int *)sub_552200((_DWORD *)solid + 30, 4);
    rf_geomod_face_corner_append(link, *v16, 0.13453799, 1.421821, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v17 = (int *)sub_552200((_DWORD *)solid + 30, 1);
    rf_geomod_face_corner_append(link, *v17, 0.333152, 0.898781, 0.0, 0.0);
    v18 = (int *)sub_552200((_DWORD *)solid + 30, 3);
    rf_geomod_face_corner_append(link, *v18, 0.43071499, 1.6435601, 0.0, 0.0);
    v19 = (int *)sub_552200((_DWORD *)solid + 30, 5);
    rf_geomod_face_corner_append(link, *v19, 0.59269702, 1.306931, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v20 = (int *)sub_552200((_DWORD *)solid + 30, 0);
    rf_geomod_face_corner_append(link, *v20, 1.301614, 0.67993402, 0.0, 0.0);
    v21 = (int *)sub_552200((_DWORD *)solid + 30, 2);
    rf_geomod_face_corner_append(link, *v21, 0.72078198, 0.76556998, 0.0, 0.0);
    v22 = (int *)sub_552200((_DWORD *)solid + 30, 6);
    rf_geomod_face_corner_append(link, *v22, 1.006647, 1.006889, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v23 = (int *)sub_552200((_DWORD *)solid + 30, 7);
    rf_geomod_face_corner_append(link, *v23, 0.31796899, 1.172604, 0.0, 0.0);
    v24 = (int *)sub_552200((_DWORD *)solid + 30, 0);
    rf_geomod_face_corner_append(link, *v24, 0.30161399, 0.67993402, 0.0, 0.0);
    v25 = (int *)sub_552200((_DWORD *)solid + 30, 6);
    rf_geomod_face_corner_append(link, *v25, 0.0066470001, 1.006889, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v26 = (int *)sub_552200((_DWORD *)solid + 30, 1);
    rf_geomod_face_corner_append(link, *v26, 1.3331521, 0.898781, 0.0, 0.0);
    v27 = (int *)sub_552200((_DWORD *)solid + 30, 0);
    rf_geomod_face_corner_append(link, *v27, 0.80161399, 0.67993402, 0.0, 0.0);
    v28 = (int *)sub_552200((_DWORD *)solid + 30, 7);
    rf_geomod_face_corner_append(link, *v28, 0.81796902, 1.172604, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v29 = (int *)sub_552200((_DWORD *)solid + 30, 1);
    rf_geomod_face_corner_append(link, *v29, 1.3331521, 0.898781, 0.0, 0.0);
    v30 = (int *)sub_552200((_DWORD *)solid + 30, 7);
    rf_geomod_face_corner_append(link, *v30, 0.81796902, 1.172604, 0.0, 0.0);
    v31 = (int *)sub_552200((_DWORD *)solid + 30, 4);
    rf_geomod_face_corner_append(link, *v31, 1.1345381, 1.421821, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v32 = (int *)sub_552200((_DWORD *)solid + 30, 1);
    rf_geomod_face_corner_append(link, *v32, 0.333152, 0.898781, 0.0, 0.0);
    v33 = (int *)sub_552200((_DWORD *)solid + 30, 5);
    rf_geomod_face_corner_append(link, *v33, 0.59269702, 1.306931, 0.0, 0.0);
    v34 = (int *)sub_552200((_DWORD *)solid + 30, 2);
    rf_geomod_face_corner_append(link, *v34, 0.72078198, 0.76556998, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v35 = (int *)sub_552200((_DWORD *)solid + 30, 6);
    rf_geomod_face_corner_append(link, *v35, 1.006647, 1.006889, 0.0, 0.0);
    v36 = (int *)sub_552200((_DWORD *)solid + 30, 2);
    rf_geomod_face_corner_append(link, *v36, 0.72078198, 0.76556998, 0.0, 0.0);
    v37 = (int *)sub_552200((_DWORD *)solid + 30, 5);
    rf_geomod_face_corner_append(link, *v37, 0.59269702, 1.306931, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v38 = (int *)sub_552200((_DWORD *)solid + 30, 3);
    rf_geomod_face_corner_append(link, *v38, 0.43071499, 0.64355999, 0.0, 0.0);
    v39 = (int *)sub_552200((_DWORD *)solid + 30, 4);
    rf_geomod_face_corner_append(link, *v39, 0.13453799, 0.421821, 0.0, 0.0);
    v40 = (int *)sub_552200((_DWORD *)solid + 30, 8);
    rf_geomod_face_corner_append(link, *v40, 0.013291, 0.76702797, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v41 = (int *)sub_552200((_DWORD *)solid + 30, 9);
    rf_geomod_face_corner_append(link, *v41, 0.91800702, 0.71861303, 0.0, 0.0);
    v42 = (int *)sub_552200((_DWORD *)solid + 30, 5);
    rf_geomod_face_corner_append(link, *v42, 0.59269702, 0.30693099, 0.0, 0.0);
    v43 = (int *)sub_552200((_DWORD *)solid + 30, 3);
    rf_geomod_face_corner_append(link, *v43, 0.43071499, 0.64355999, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v44 = (int *)sub_552200((_DWORD *)solid + 30, 6);
    rf_geomod_face_corner_append(link, *v44, 1.006647, 0.0068890001, 0.0, 0.0);
    v45 = (int *)sub_552200((_DWORD *)solid + 30, 5);
    rf_geomod_face_corner_append(link, *v45, 0.59269702, 0.30693099, 0.0, 0.0);
    v46 = (int *)sub_552200((_DWORD *)solid + 30, 9);
    rf_geomod_face_corner_append(link, *v46, 0.91800702, 0.71861303, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v47 = (int *)sub_552200((_DWORD *)solid + 30, 7);
    rf_geomod_face_corner_append(link, *v47, 0.81796902, 0.17260399, 0.0, 0.0);
    v48 = (int *)sub_552200((_DWORD *)solid + 30, 9);
    rf_geomod_face_corner_append(link, *v48, 0.41800699, 0.71861303, 0.0, 0.0);
    v49 = (int *)sub_552200((_DWORD *)solid + 30, 8);
    rf_geomod_face_corner_append(link, *v49, 1.013291, 0.76702797, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v50 = (int *)sub_552200((_DWORD *)solid + 30, 6);
    rf_geomod_face_corner_append(link, *v50, 1.006647, 0.0068890001, 0.0, 0.0);
    v51 = (int *)sub_552200((_DWORD *)solid + 30, 9);
    rf_geomod_face_corner_append(link, *v51, 0.91800702, 0.71861303, 0.0, 0.0);
    v52 = (int *)sub_552200((_DWORD *)solid + 30, 7);
    rf_geomod_face_corner_append(link, *v52, 1.317969, 0.17260399, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v53 = (int *)sub_552200((_DWORD *)solid + 30, 4);
    rf_geomod_face_corner_append(link, *v53, 1.1345381, 0.421821, 0.0, 0.0);
    v54 = (int *)sub_552200((_DWORD *)solid + 30, 7);
    rf_geomod_face_corner_append(link, *v54, 0.81796902, 0.17260399, 0.0, 0.0);
    v55 = (int *)sub_552200((_DWORD *)solid + 30, 8);
    rf_geomod_face_corner_append(link, *v55, 1.013291, 0.76702797, 0.0, 0.0);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    v56 = (int *)sub_552200((_DWORD *)solid + 30, 3);
    rf_geomod_face_corner_append(link, *v56, 1.430715, 0.64355999, 0.0, 0.0);
    v57 = (int *)sub_552200((_DWORD *)solid + 30, 8);
    rf_geomod_face_corner_append(link, *v57, 1.013291, 0.76702797, 0.0, 0.0);
    v58 = (int *)sub_552200((_DWORD *)solid + 30, 9);
    rf_geomod_face_corner_append(link, *v58, 0.41800699, 0.71861303, 0.0, 0.0);
    rf_solid_finalize_bounds((float *)solid);
    room = operator new(0x1CCu);
    v838 = 1;
    if ( room )
      v611 = (int *)rf_room460_construct_register(room, solid, (const float *)solid + 18, (const float *)solid + 21);
    else
      v611 = nullptr;
    v791 = v611;
    v838 = -1;
    v833 = (float *)v611;
    for ( link = (float *)rf_receiver_get_first_dword((char *)solid + 112);
          link;
          link = (float *)rf_solid_face_next_link((int)link) )
    {
      rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
      rf_geomod_room_face_attach(v833, (int)link);
    }
    rf_room_face_spatial_tree_rebuild((int *)v833);
    return solid;
  }
  else if ( !_stricmp(String1, "bit_driller_double.v3d") )
  {
    strcpy(v826, "bit_driller_double.v3d");
    v788 = operator new(0x378u);
    v838 = 2;
    if ( v788 )
      v610 = rf_solid888_construct((void **)v788);
    else
      v610 = nullptr;
    v789 = v610;
    v838 = -1;
    v830 = v610;
    rf_vector3_default_construct_noop(v829);
    v60 = rf_vector3_set_components_return_destination(v787, -3.4507489, 2.871134, -1.104167);
    rf_vector_copy(v829, v786, v60);
    rf_solid_vertex_copy_append(v830, v829);
    v61 = rf_vector3_set_components_return_destination(v785, 2.5584171, -2.129576, 2.1759961);
    rf_vector_copy(v829, v784, v61);
    rf_solid_vertex_copy_append(v830, v829);
    v62 = rf_vector3_set_components_return_destination(v783, -3.906826, 2.6731169, -2.1759961);
    rf_vector_copy(v829, v782, v62);
    rf_solid_vertex_copy_append(v830, v829);
    v63 = rf_vector3_set_components_return_destination(v781, -2.209038, 2.6323011, -2.1759961);
    rf_vector_copy(v829, v780, v63);
    rf_solid_vertex_copy_append(v830, v829);
    v64 = rf_vector3_set_components_return_destination(v779, -4.7933331, -2.3163559, 1.104167);
    rf_vector_copy(v829, v778, v64);
    rf_solid_vertex_copy_append(v830, v829);
    v65 = rf_vector3_set_components_return_destination(v777, -5.5141888, -1.546513, 1.104167);
    rf_vector_copy(v829, v776, v65);
    rf_solid_vertex_copy_append(v830, v829);
    v66 = rf_vector3_set_components_return_destination(v775, -3.0052149, 1.917323, 2.1759961);
    rf_vector_copy(v829, v774, v66);
    rf_solid_vertex_copy_append(v830, v829);
    v67 = rf_vector3_set_components_return_destination(v773, 5.6633778, -0.77157199, 1.104167);
    rf_vector_copy(v829, v772, v67);
    rf_solid_vertex_copy_append(v830, v829);
    v68 = rf_vector3_set_components_return_destination(v771, 5.469151, -1.66211, 1.104167);
    rf_vector_copy(v829, v770, v68);
    rf_solid_vertex_copy_append(v830, v829);
    v69 = rf_vector3_set_components_return_destination(v769, 3.3439219, 2.6011469, -2.1759961);
    rf_vector_copy(v829, v768, v69);
    rf_solid_vertex_copy_append(v830, v829);
    v70 = rf_vector3_set_components_return_destination(v767, 4.153048, -1.5771869, 2.1759961);
    rf_vector_copy(v829, v766, v70);
    rf_solid_vertex_copy_append(v830, v829);
    v71 = rf_vector3_set_components_return_destination(v765, -4.8946791, 2.3114481, 1.104166);
    rf_vector_copy(v829, v764, v71);
    rf_solid_vertex_copy_append(v830, v829);
    v72 = rf_vector3_set_components_return_destination(v763, 4.3822751, 2.2871339, -2.1759961);
    rf_vector_copy(v829, v762, v72);
    rf_solid_vertex_copy_append(v830, v829);
    v73 = rf_vector3_set_components_return_destination(v761, -4.2873712, -1.069356, 2.1759961);
    rf_vector_copy(v829, v760, v73);
    rf_solid_vertex_copy_append(v830, v829);
    v74 = rf_vector3_set_components_return_destination(v759, 4.1943622, 2.618377, -1.104167);
    rf_vector_copy(v829, v758, v74);
    rf_solid_vertex_copy_append(v830, v829);
    v75 = rf_vector3_set_components_return_destination(v757, -5.1533518, 1.837631, -2.1759961);
    rf_vector_copy(v829, v756, v75);
    rf_solid_vertex_copy_append(v830, v829);
    v76 = rf_vector3_set_components_return_destination(v755, 5.193778, -2.198055, 1.104167);
    rf_vector_copy(v829, v754, v76);
    rf_solid_vertex_copy_append(v830, v829);
    v77 = rf_vector3_set_components_return_destination(v753, -3.9150879, 1.307479, 2.1759961);
    rf_vector_copy(v829, v752, v77);
    rf_solid_vertex_copy_append(v830, v829);
    v78 = rf_vector3_set_components_return_destination(v751, 5.640873, -0.59214401, -2.1759961);
    rf_vector_copy(v829, v750, v78);
    rf_solid_vertex_copy_append(v830, v829);
    v79 = rf_vector3_set_components_return_destination(v749, -2.819248, -1.986246, 2.1759961);
    rf_vector_copy(v829, v748, v79);
    rf_solid_vertex_copy_append(v830, v829);
    v80 = rf_vector3_set_components_return_destination(v747, -4.8946791, 2.3114481, -1.104167);
    rf_vector_copy(v829, v746, v80);
    rf_solid_vertex_copy_append(v830, v829);
    v81 = rf_vector3_set_components_return_destination(v745, 5.3866882, -2.114361, -2.1759961);
    rf_vector_copy(v829, v744, v81);
    rf_solid_vertex_copy_append(v830, v829);
    v82 = rf_vector3_set_components_return_destination(v743, 5.5605278, -0.036561001, 1.104167);
    rf_vector_copy(v829, v742, v82);
    rf_solid_vertex_copy_append(v830, v829);
    v83 = rf_vector3_set_components_return_destination(v741, 4.3385839, -0.466079, 2.1759961);
    rf_vector_copy(v829, v740, v83);
    rf_solid_vertex_copy_append(v830, v829);
    v84 = rf_vector3_set_components_return_destination(v739, 3.202044, -2.871134, -2.1759951);
    rf_vector_copy(v829, v738, v84);
    rf_solid_vertex_copy_append(v830, v829);
    v85 = rf_vector3_set_components_return_destination(v737, 4.4376488, -2.5883579, 1.104167);
    rf_vector_copy(v829, v736, v85);
    rf_solid_vertex_copy_append(v830, v829);
    v86 = rf_vector3_set_components_return_destination(v735, -2.7860889, -2.6685491, 1.104167);
    rf_vector_copy(v829, v734, v86);
    rf_solid_vertex_copy_append(v830, v829);
    v87 = rf_vector3_set_components_return_destination(v733, -3.652051, -2.6747711, -2.1759951);
    rf_vector_copy(v829, v732, v87);
    rf_solid_vertex_copy_append(v830, v829);
    v88 = rf_vector3_set_components_return_destination(v731, -4.7933331, -2.3163559, -1.104167);
    rf_vector_copy(v829, v730, v88);
    rf_solid_vertex_copy_append(v830, v829);
    v89 = rf_vector3_set_components_return_destination(v729, -5.2264552, 1.6874551, 1.104166);
    rf_vector_copy(v829, v728, v89);
    rf_solid_vertex_copy_append(v830, v829);
    v90 = rf_vector3_set_components_return_destination(v727, -5.6633778, -1.418633, -2.1759961);
    rf_vector_copy(v829, v726, v90);
    rf_solid_vertex_copy_append(v830, v829);
    v91 = rf_vector3_set_components_return_destination(v725, 4.1943622, 2.6183779, 1.104166);
    rf_vector_copy(v829, v724, v91);
    rf_solid_vertex_copy_append(v830, v829);
    v92 = rf_vector3_set_components_return_destination(v723, 3.419899, 1.635583, 2.1759961);
    rf_vector_copy(v829, v722, v92);
    rf_solid_vertex_copy_append(v830, v829);
    v93 = rf_vector3_set_components_return_destination(v721, -4.1209359, 2.779258, 1.104166);
    rf_vector_copy(v829, v720, v93);
    rf_solid_vertex_copy_append(v830, v829);
    rf_geomod_face_metadata_init(v831);
    v831[2] = -1;
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v94 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v94, 1.133463, 0.96900398, 0.0, 0.0);
    v95 = (int *)sub_552200((_DWORD *)v830 + 30, 0);
    rf_geomod_face_corner_append(i, *v95, 0.96619803, 1.275522, 0.0, 0.0);
    v96 = (int *)sub_552200((_DWORD *)v830 + 30, 3);
    rf_geomod_face_corner_append(i, *v96, 0.98320001, 1.50668, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v97 = (int *)sub_552200((_DWORD *)v830 + 30, 12);
    rf_geomod_face_corner_append(i, *v97, 0.46033499, 0.90704399, 0.0, 0.0);
    v98 = (int *)sub_552200((_DWORD *)v830 + 30, 14);
    rf_geomod_face_corner_append(i, *v98, 0.52962703, 0.74829501, 0.0, 0.0);
    v99 = (int *)sub_552200((_DWORD *)v830 + 30, 9);
    rf_geomod_face_corner_append(i, *v99, 0.34953901, 0.81407499, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v100 = (int *)sub_552200((_DWORD *)v830 + 30, 17);
    rf_geomod_face_corner_append(i, *v100, 0.67925799, 0.35188299, 0.0, 0.0);
    v101 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v101, 0.55333799, 0.133463, 0.0, 0.0);
    v102 = (int *)sub_552200((_DWORD *)v830 + 30, 6);
    rf_geomod_face_corner_append(i, *v102, 0.53173602, 0.392676, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v103 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v103, 0.133463, 0.96900398, 0.0, 0.0);
    v104 = (int *)sub_552200((_DWORD *)v830 + 30, 9);
    rf_geomod_face_corner_append(i, *v104, 0.34953901, 1.814075, 0.0, 0.0);
    v105 = (int *)sub_552200((_DWORD *)v830 + 30, 31);
    rf_geomod_face_corner_append(i, *v105, 0.749668, 1.486061, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v106 = (int *)sub_552200((_DWORD *)v830 + 30, 31);
    rf_geomod_face_corner_append(i, *v106, 0.749668, 0.48606101, 0.0, 0.0);
    v107 = (int *)sub_552200((_DWORD *)v830 + 30, 9);
    rf_geomod_face_corner_append(i, *v107, 0.34953901, 0.81407499, 0.0, 0.0);
    v108 = (int *)sub_552200((_DWORD *)v830 + 30, 14);
    rf_geomod_face_corner_append(i, *v108, 0.52962703, 0.74829501, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v109 = (int *)sub_552200((_DWORD *)v830 + 30, 4);
    rf_geomod_face_corner_append(i, *v109, 0.601228, 0.191624, 0.0, 0.0);
    v110 = (int *)sub_552200((_DWORD *)v830 + 30, 27);
    rf_geomod_face_corner_append(i, *v110, 0.805444, 0.68402803, 0.0, 0.0);
    v111 = (int *)sub_552200((_DWORD *)v830 + 30, 28);
    rf_geomod_face_corner_append(i, *v111, 0.82126898, 0.45385799, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v112 = (int *)sub_552200((_DWORD *)v830 + 30, 25);
    rf_geomod_face_corner_append(i, *v112, 0.39742699, 0.78181797, 0.0, 0.0);
    v113 = (int *)sub_552200((_DWORD *)v830 + 30, 21);
    rf_geomod_face_corner_append(i, *v113, 0.25959599, 1.2156841, 0.0, 0.0);
    v114 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v114, 0.54379201, 1.095736, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v115 = (int *)sub_552200((_DWORD *)v830 + 30, 13);
    rf_geomod_face_corner_append(i, *v115, 0.52949399, 0.034924999, 0.0, 0.0);
    v116 = (int *)sub_552200((_DWORD *)v830 + 30, 19);
    rf_geomod_face_corner_append(i, *v116, 0.34276, 0.191613, 0.0, 0.0);
    v117 = (int *)sub_552200((_DWORD *)v830 + 30, 5);
    rf_geomod_face_corner_append(i, *v117, 0.71324801, 0.097629003, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v118 = (int *)sub_552200((_DWORD *)v830 + 30, 31);
    rf_geomod_face_corner_append(i, *v118, 0.749668, 0.48606101, 0.0, 0.0);
    v119 = (int *)sub_552200((_DWORD *)v830 + 30, 12);
    rf_geomod_face_corner_append(i, *v119, 0.46033499, 0.90704399, 0.0, 0.0);
    v120 = (int *)sub_552200((_DWORD *)v830 + 30, 22);
    rf_geomod_face_corner_append(i, *v120, 1.038038, 0.72803199, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v121 = (int *)sub_552200((_DWORD *)v830 + 30, 19);
    rf_geomod_face_corner_append(i, *v121, 0.90020198, 0.191613, 0.0, 0.0);
    v122 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v122, 0.53207499, 0.49213001, 0.0, 0.0);
    v123 = (int *)sub_552200((_DWORD *)v830 + 30, 26);
    rf_geomod_face_corner_append(i, *v123, 0.96454298, 0.357741, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v124 = (int *)sub_552200((_DWORD *)v830 + 30, 11);
    rf_geomod_face_corner_append(i, *v124, 0.67376202, 0.095541999, 0.0, 0.0);
    v125 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v125, 0.55333799, 0.133463, 0.0, 0.0);
    v126 = (int *)sub_552200((_DWORD *)v830 + 30, 17);
    rf_geomod_face_corner_append(i, *v126, 0.67925799, 0.35188299, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v127 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v127, 1.06127, 0.469365, 0.0, 0.0);
    v128 = (int *)sub_552200((_DWORD *)v830 + 30, 28);
    rf_geomod_face_corner_append(i, *v128, 0.82126898, 0.45385799, 0.0, 0.0);
    v129 = (int *)sub_552200((_DWORD *)v830 + 30, 27);
    rf_geomod_face_corner_append(i, *v129, 0.805444, 0.68402803, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v130 = (int *)sub_552200((_DWORD *)v830 + 30, 8);
    rf_geomod_face_corner_append(i, *v130, 0.20694201, 0.80808699, 0.0, 0.0);
    v131 = (int *)sub_552200((_DWORD *)v830 + 30, 18);
    rf_geomod_face_corner_append(i, *v131, 0.08461, 1.1530941, 0.0, 0.0);
    v132 = (int *)sub_552200((_DWORD *)v830 + 30, 21);
    rf_geomod_face_corner_append(i, *v132, 0.25959599, 1.2156841, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v133 = (int *)sub_552200((_DWORD *)v830 + 30, 7);
    rf_geomod_face_corner_append(i, *v133, 0.100209, 0.77481103, 0.0, 0.0);
    v134 = (int *)sub_552200((_DWORD *)v830 + 30, 18);
    rf_geomod_face_corner_append(i, *v134, 0.08461, 1.1530941, 0.0, 0.0);
    v135 = (int *)sub_552200((_DWORD *)v830 + 30, 8);
    rf_geomod_face_corner_append(i, *v135, 0.20694201, 0.80808699, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v136 = (int *)sub_552200((_DWORD *)v830 + 30, 8);
    rf_geomod_face_corner_append(i, *v136, 0.20694201, 0.80808699, 0.0, 0.0);
    v137 = (int *)sub_552200((_DWORD *)v830 + 30, 16);
    rf_geomod_face_corner_append(i, *v137, 0.28636, 0.81648099, 0.0, 0.0);
    v138 = (int *)sub_552200((_DWORD *)v830 + 30, 10);
    rf_geomod_face_corner_append(i, *v138, 0.324633, 0.57968301, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v139 = (int *)sub_552200((_DWORD *)v830 + 30, 16);
    rf_geomod_face_corner_append(i, *v139, 0.28636, 0.81648099, 0.0, 0.0);
    v140 = (int *)sub_552200((_DWORD *)v830 + 30, 21);
    rf_geomod_face_corner_append(i, *v140, 0.25959599, 1.2156841, 0.0, 0.0);
    v141 = (int *)sub_552200((_DWORD *)v830 + 30, 25);
    rf_geomod_face_corner_append(i, *v141, 0.39742699, 0.78181797, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v142 = (int *)sub_552200((_DWORD *)v830 + 30, 26);
    rf_geomod_face_corner_append(i, *v142, 0.403258, 0.357741, 0.0, 0.0);
    v143 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v143, 0.31479001, 1.095736, 0.0, 0.0);
    v144 = (int *)sub_552200((_DWORD *)v830 + 30, 27);
    rf_geomod_face_corner_append(i, *v144, 0.805444, 0.68402803, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v145 = (int *)sub_552200((_DWORD *)v830 + 30, 25);
    rf_geomod_face_corner_append(i, *v145, 0.89786297, 0.78181797, 0.0, 0.0);
    v146 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v146, 1.31479, 1.095736, 0.0, 0.0);
    v147 = (int *)sub_552200((_DWORD *)v830 + 30, 26);
    rf_geomod_face_corner_append(i, *v147, 1.403258, 0.357741, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v148 = (int *)sub_552200((_DWORD *)v830 + 30, 5);
    rf_geomod_face_corner_append(i, *v148, 0.71324801, 0.097629003, 0.0, 0.0);
    v149 = (int *)sub_552200((_DWORD *)v830 + 30, 28);
    rf_geomod_face_corner_append(i, *v149, 0.82126898, 0.45385799, 0.0, 0.0);
    v150 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v150, 1.06127, 0.469365, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v151 = (int *)sub_552200((_DWORD *)v830 + 30, 4);
    rf_geomod_face_corner_append(i, *v151, 0.601228, 0.191624, 0.0, 0.0);
    v152 = (int *)sub_552200((_DWORD *)v830 + 30, 28);
    rf_geomod_face_corner_append(i, *v152, 0.82126898, 0.45385799, 0.0, 0.0);
    v153 = (int *)sub_552200((_DWORD *)v830 + 30, 5);
    rf_geomod_face_corner_append(i, *v153, 0.71324801, 0.097629003, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v154 = (int *)sub_552200((_DWORD *)v830 + 30, 11);
    rf_geomod_face_corner_append(i, *v154, 0.32623801, 0.93718398, 0.0, 0.0);
    v155 = (int *)sub_552200((_DWORD *)v830 + 30, 15);
    rf_geomod_face_corner_append(i, *v155, 0.254567, 1.3329999, 0.0, 0.0);
    v156 = (int *)sub_552200((_DWORD *)v830 + 30, 20);
    rf_geomod_face_corner_append(i, *v156, 0.32623801, 1.199419, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v157 = (int *)sub_552200((_DWORD *)v830 + 30, 31);
    rf_geomod_face_corner_append(i, *v157, 0.749668, 0.48606101, 0.0, 0.0);
    v158 = (int *)sub_552200((_DWORD *)v830 + 30, 14);
    rf_geomod_face_corner_append(i, *v158, 0.52962703, 0.74829501, 0.0, 0.0);
    v159 = (int *)sub_552200((_DWORD *)v830 + 30, 12);
    rf_geomod_face_corner_append(i, *v159, 0.46033499, 0.90704399, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v160 = (int *)sub_552200((_DWORD *)v830 + 30, 29);
    rf_geomod_face_corner_append(i, *v160, 1.232703, 0.94613898, 0.0, 0.0);
    v161 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v161, 0.88347501, 1.469365, 0.0, 0.0);
    v162 = (int *)sub_552200((_DWORD *)v830 + 30, 15);
    rf_geomod_face_corner_append(i, *v162, 1.254567, 1.3329999, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v163 = (int *)sub_552200((_DWORD *)v830 + 30, 5);
    rf_geomod_face_corner_append(i, *v163, 0.88511401, 1.097629, 0.0, 0.0);
    v164 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v164, 0.88347501, 1.469365, 0.0, 0.0);
    v165 = (int *)sub_552200((_DWORD *)v830 + 30, 29);
    rf_geomod_face_corner_append(i, *v165, 1.232703, 0.94613898, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v166 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v166, 0.44666201, 0.96900398, 0.0, 0.0);
    v167 = (int *)sub_552200((_DWORD *)v830 + 30, 20);
    rf_geomod_face_corner_append(i, *v167, 0.32623801, 1.199419, 0.0, 0.0);
    v168 = (int *)sub_552200((_DWORD *)v830 + 30, 2);
    rf_geomod_face_corner_append(i, *v168, 0.45667201, 1.379895, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v169 = (int *)sub_552200((_DWORD *)v830 + 30, 11);
    rf_geomod_face_corner_append(i, *v169, 0.32623801, 0.93718398, 0.0, 0.0);
    v170 = (int *)sub_552200((_DWORD *)v830 + 30, 20);
    rf_geomod_face_corner_append(i, *v170, 0.32623801, 1.199419, 0.0, 0.0);
    v171 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v171, 0.44666201, 0.96900398, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v172 = (int *)sub_552200((_DWORD *)v830 + 30, 27);
    rf_geomod_face_corner_append(i, *v172, 0.95187402, 1.194556, 0.0, 0.0);
    v173 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v173, 1.456208, 1.68521, 0.0, 0.0);
    v174 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v174, 0.88347501, 0.93873, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v175 = (int *)sub_552200((_DWORD *)v830 + 30, 23);
    rf_geomod_face_corner_append(i, *v175, 0.196906, 0.533997, 0.0, 0.0);
    v176 = (int *)sub_552200((_DWORD *)v830 + 30, 32);
    rf_geomod_face_corner_append(i, *v176, 0.076950997, 0.35439801, 0.0, 0.0);
    v177 = (int *)sub_552200((_DWORD *)v830 + 30, 22);
    rf_geomod_face_corner_append(i, *v177, 0.037328999, 0.72803199, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v178 = (int *)sub_552200((_DWORD *)v830 + 30, 15);
    rf_geomod_face_corner_append(i, *v178, 1.254567, 0.77621597, 0.0, 0.0);
    v179 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v179, 0.88347501, 0.93873, 0.0, 0.0);
    v180 = (int *)sub_552200((_DWORD *)v830 + 30, 2);
    rf_geomod_face_corner_append(i, *v180, 1.456672, 0.83210301, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v181 = (int *)sub_552200((_DWORD *)v830 + 30, 2);
    rf_geomod_face_corner_append(i, *v181, 1.456672, 0.83210301, 0.0, 0.0);
    v182 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v182, 0.88347501, 0.93873, 0.0, 0.0);
    v183 = (int *)sub_552200((_DWORD *)v830 + 30, 3);
    rf_geomod_face_corner_append(i, *v183, 1.615296, 0.98320001, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v184 = (int *)sub_552200((_DWORD *)v830 + 30, 30);
    rf_geomod_face_corner_append(i, *v184, 0.88347501, 0.93873, 0.0, 0.0);
    v185 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v185, 1.456208, 1.68521, 0.0, 0.0);
    v186 = (int *)sub_552200((_DWORD *)v830 + 30, 3);
    rf_geomod_face_corner_append(i, *v186, 1.615296, 0.98320001, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v187 = (int *)sub_552200((_DWORD *)v830 + 30, 3);
    rf_geomod_face_corner_append(i, *v187, 0.61529601, 0.98320001, 0.0, 0.0);
    v188 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v188, 0.45620799, 1.68521, 0.0, 0.0);
    v189 = (int *)sub_552200((_DWORD *)v830 + 30, 9);
    rf_geomod_face_corner_append(i, *v189, 1.011318, 1.349539, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v190 = (int *)sub_552200((_DWORD *)v830 + 30, 17);
    rf_geomod_face_corner_append(i, *v190, 0.67925799, 0.35188299, 0.0, 0.0);
    v191 = (int *)sub_552200((_DWORD *)v830 + 30, 13);
    rf_geomod_face_corner_append(i, *v191, 0.95012897, 0.47050601, 0.0, 0.0);
    v192 = (int *)sub_552200((_DWORD *)v830 + 30, 29);
    rf_geomod_face_corner_append(i, *v192, 0.76729703, 0.106214, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v193 = (int *)sub_552200((_DWORD *)v830 + 30, 25);
    rf_geomod_face_corner_append(i, *v193, 0.39742699, 0.78181797, 0.0, 0.0);
    v194 = (int *)sub_552200((_DWORD *)v830 + 30, 10);
    rf_geomod_face_corner_append(i, *v194, 0.324633, 0.57968301, 0.0, 0.0);
    v195 = (int *)sub_552200((_DWORD *)v830 + 30, 16);
    rf_geomod_face_corner_append(i, *v195, 0.28636, 0.81648099, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v196 = (int *)sub_552200((_DWORD *)v830 + 30, 9);
    rf_geomod_face_corner_append(i, *v196, 1.011318, 0.34953901, 0.0, 0.0);
    v197 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v197, 0.45620799, 0.68520999, 0.0, 0.0);
    v198 = (int *)sub_552200((_DWORD *)v830 + 30, 12);
    rf_geomod_face_corner_append(i, *v198, 1.079728, 0.46033499, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v199 = (int *)sub_552200((_DWORD *)v830 + 30, 12);
    rf_geomod_face_corner_append(i, *v199, 1.079728, 0.46033499, 0.0, 0.0);
    v200 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v200, 0.45620799, 0.68520999, 0.0, 0.0);
    v201 = (int *)sub_552200((_DWORD *)v830 + 30, 18);
    rf_geomod_face_corner_append(i, *v201, 0.91539001, 0.75356603, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v202 = (int *)sub_552200((_DWORD *)v830 + 30, 18);
    rf_geomod_face_corner_append(i, *v202, 0.91539001, 0.75356603, 0.0, 0.0);
    v203 = (int *)sub_552200((_DWORD *)v830 + 30, 24);
    rf_geomod_face_corner_append(i, *v203, 0.45620799, 0.68520999, 0.0, 0.0);
    v204 = (int *)sub_552200((_DWORD *)v830 + 30, 21);
    rf_geomod_face_corner_append(i, *v204, 0.74040401, 0.82815802, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v205 = (int *)sub_552200((_DWORD *)v830 + 30, 13);
    rf_geomod_face_corner_append(i, *v205, 0.95012897, 0.47050601, 0.0, 0.0);
    v206 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v206, 0.53207499, 1.0153821, 0.0, 0.0);
    v207 = (int *)sub_552200((_DWORD *)v830 + 30, 19);
    rf_geomod_face_corner_append(i, *v207, 0.90020198, 0.65723997, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v208 = (int *)sub_552200((_DWORD *)v830 + 30, 26);
    rf_geomod_face_corner_append(i, *v208, 1.403258, 0.357741, 0.0, 0.0);
    v209 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v209, 0.98461801, 0.49213001, 0.0, 0.0);
    v210 = (int *)sub_552200((_DWORD *)v830 + 30, 25);
    rf_geomod_face_corner_append(i, *v210, 0.89786297, 0.78181797, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v211 = (int *)sub_552200((_DWORD *)v830 + 30, 6);
    rf_geomod_face_corner_append(i, *v211, 0.53173602, 0.392676, 0.0, 0.0);
    v212 = (int *)sub_552200((_DWORD *)v830 + 30, 13);
    rf_geomod_face_corner_append(i, *v212, 0.95012897, 0.47050601, 0.0, 0.0);
    v213 = (int *)sub_552200((_DWORD *)v830 + 30, 17);
    rf_geomod_face_corner_append(i, *v213, 0.67925799, 0.35188299, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v214 = (int *)sub_552200((_DWORD *)v830 + 30, 29);
    rf_geomod_face_corner_append(i, *v214, 0.76729703, 0.106214, 0.0, 0.0);
    v215 = (int *)sub_552200((_DWORD *)v830 + 30, 11);
    rf_geomod_face_corner_append(i, *v215, 0.67376202, 0.095541999, 0.0, 0.0);
    v216 = (int *)sub_552200((_DWORD *)v830 + 30, 17);
    rf_geomod_face_corner_append(i, *v216, 0.67925799, 0.35188299, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v217 = (int *)sub_552200((_DWORD *)v830 + 30, 6);
    rf_geomod_face_corner_append(i, *v217, 0.53173602, 0.392676, 0.0, 0.0);
    v218 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v218, 0.53207499, 1.0153821, 0.0, 0.0);
    v219 = (int *)sub_552200((_DWORD *)v830 + 30, 13);
    rf_geomod_face_corner_append(i, *v219, 0.95012897, 0.47050601, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v220 = (int *)sub_552200((_DWORD *)v830 + 30, 32);
    rf_geomod_face_corner_append(i, *v220, 0.076950997, 0.85123903, 0.0, 0.0);
    v221 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v221, 0.53207499, 1.0153821, 0.0, 0.0);
    v222 = (int *)sub_552200((_DWORD *)v830 + 30, 6);
    rf_geomod_face_corner_append(i, *v222, 0.53173602, 0.392676, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v223 = (int *)sub_552200((_DWORD *)v830 + 30, 29);
    rf_geomod_face_corner_append(i, *v223, 0.232703, 0.94613898, 0.0, 0.0);
    v224 = (int *)sub_552200((_DWORD *)v830 + 30, 15);
    rf_geomod_face_corner_append(i, *v224, 0.254567, 1.3329999, 0.0, 0.0);
    v225 = (int *)sub_552200((_DWORD *)v830 + 30, 11);
    rf_geomod_face_corner_append(i, *v225, 0.32623801, 0.93718398, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v226 = (int *)sub_552200((_DWORD *)v830 + 30, 5);
    rf_geomod_face_corner_append(i, *v226, 1.114886, 0.28675199, 0.0, 0.0);
    v227 = (int *)sub_552200((_DWORD *)v830 + 30, 19);
    rf_geomod_face_corner_append(i, *v227, 0.90020198, 0.65723997, 0.0, 0.0);
    v228 = (int *)sub_552200((_DWORD *)v830 + 30, 4);
    rf_geomod_face_corner_append(i, *v228, 1.122003, 0.398772, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v229 = (int *)sub_552200((_DWORD *)v830 + 30, 22);
    rf_geomod_face_corner_append(i, *v229, 1.038038, 0.72803199, 0.0, 0.0);
    v230 = (int *)sub_552200((_DWORD *)v830 + 30, 32);
    rf_geomod_face_corner_append(i, *v230, 0.85123903, 0.35439801, 0.0, 0.0);
    v231 = (int *)sub_552200((_DWORD *)v830 + 30, 31);
    rf_geomod_face_corner_append(i, *v231, 0.749668, 0.48606101, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v232 = (int *)sub_552200((_DWORD *)v830 + 30, 23);
    rf_geomod_face_corner_append(i, *v232, 0.196906, 1.065276, 0.0, 0.0);
    v233 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v233, 0.53207499, 1.0153821, 0.0, 0.0);
    v234 = (int *)sub_552200((_DWORD *)v830 + 30, 32);
    rf_geomod_face_corner_append(i, *v234, 0.076950997, 0.85123903, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v235 = (int *)sub_552200((_DWORD *)v830 + 30, 10);
    rf_geomod_face_corner_append(i, *v235, 0.324633, 0.119723, 0.0, 0.0);
    v236 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v236, 0.53207499, 0.015382, 0.0, 0.0);
    v237 = (int *)sub_552200((_DWORD *)v830 + 30, 23);
    rf_geomod_face_corner_append(i, *v237, 0.196906, 0.065275997, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v238 = (int *)sub_552200((_DWORD *)v830 + 30, 3);
    rf_geomod_face_corner_append(i, *v238, 0.98320001, 0.50668001, 0.0, 0.0);
    v239 = (int *)sub_552200((_DWORD *)v830 + 30, 0);
    rf_geomod_face_corner_append(i, *v239, 0.96619803, 0.27552199, 0.0, 0.0);
    v240 = (int *)sub_552200((_DWORD *)v830 + 30, 2);
    rf_geomod_face_corner_append(i, *v240, 0.83210301, 0.379895, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v241 = (int *)sub_552200((_DWORD *)v830 + 30, 10);
    rf_geomod_face_corner_append(i, *v241, 0.324633, 0.57968301, 0.0, 0.0);
    v242 = (int *)sub_552200((_DWORD *)v830 + 30, 23);
    rf_geomod_face_corner_append(i, *v242, 0.196906, 0.533997, 0.0, 0.0);
    v243 = (int *)sub_552200((_DWORD *)v830 + 30, 8);
    rf_geomod_face_corner_append(i, *v243, 0.20694201, 0.80808699, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v244 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v244, 0.44666201, 0.96900398, 0.0, 0.0);
    v245 = (int *)sub_552200((_DWORD *)v830 + 30, 2);
    rf_geomod_face_corner_append(i, *v245, 0.45667201, 1.379895, 0.0, 0.0);
    v246 = (int *)sub_552200((_DWORD *)v830 + 30, 0);
    rf_geomod_face_corner_append(i, *v246, 0.51996303, 1.275522, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v247 = (int *)sub_552200((_DWORD *)v830 + 30, 18);
    rf_geomod_face_corner_append(i, *v247, 0.75356603, 1.1530941, 0.0, 0.0);
    v248 = (int *)sub_552200((_DWORD *)v830 + 30, 22);
    rf_geomod_face_corner_append(i, *v248, 1.038038, 0.72803199, 0.0, 0.0);
    v249 = (int *)sub_552200((_DWORD *)v830 + 30, 12);
    rf_geomod_face_corner_append(i, *v249, 0.46033499, 0.90704399, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v250 = (int *)sub_552200((_DWORD *)v830 + 30, 7);
    rf_geomod_face_corner_append(i, *v250, 1.093786, 0.77481103, 0.0, 0.0);
    v251 = (int *)sub_552200((_DWORD *)v830 + 30, 22);
    rf_geomod_face_corner_append(i, *v251, 1.038038, 0.72803199, 0.0, 0.0);
    v252 = (int *)sub_552200((_DWORD *)v830 + 30, 18);
    rf_geomod_face_corner_append(i, *v252, 0.75356603, 1.1530941, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v253 = (int *)sub_552200((_DWORD *)v830 + 30, 15);
    rf_geomod_face_corner_append(i, *v253, 0.254567, 0.333, 0.0, 0.0);
    v254 = (int *)sub_552200((_DWORD *)v830 + 30, 2);
    rf_geomod_face_corner_append(i, *v254, 0.45667201, 0.379895, 0.0, 0.0);
    v255 = (int *)sub_552200((_DWORD *)v830 + 30, 20);
    rf_geomod_face_corner_append(i, *v255, 0.32623801, 0.19941901, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v256 = (int *)sub_552200((_DWORD *)v830 + 30, 26);
    rf_geomod_face_corner_append(i, *v256, 0.403258, 0.357741, 0.0, 0.0);
    v257 = (int *)sub_552200((_DWORD *)v830 + 30, 27);
    rf_geomod_face_corner_append(i, *v257, 0.805444, 0.68402803, 0.0, 0.0);
    v258 = (int *)sub_552200((_DWORD *)v830 + 30, 4);
    rf_geomod_face_corner_append(i, *v258, 0.601228, 0.191624, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v259 = (int *)sub_552200((_DWORD *)v830 + 30, 8);
    rf_geomod_face_corner_append(i, *v259, 0.20694201, 0.80808699, 0.0, 0.0);
    v260 = (int *)sub_552200((_DWORD *)v830 + 30, 23);
    rf_geomod_face_corner_append(i, *v260, 0.196906, 0.533997, 0.0, 0.0);
    v261 = (int *)sub_552200((_DWORD *)v830 + 30, 7);
    rf_geomod_face_corner_append(i, *v261, 0.100209, 0.77481103, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v262 = (int *)sub_552200((_DWORD *)v830 + 30, 26);
    rf_geomod_face_corner_append(i, *v262, 0.403258, 0.357741, 0.0, 0.0);
    v263 = (int *)sub_552200((_DWORD *)v830 + 30, 4);
    rf_geomod_face_corner_append(i, *v263, 0.601228, 0.191624, 0.0, 0.0);
    v264 = (int *)sub_552200((_DWORD *)v830 + 30, 19);
    rf_geomod_face_corner_append(i, *v264, 0.34276, 0.191613, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v265 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v265, 1.133463, 0.96900398, 0.0, 0.0);
    v266 = (int *)sub_552200((_DWORD *)v830 + 30, 3);
    rf_geomod_face_corner_append(i, *v266, 0.98320001, 1.50668, 0.0, 0.0);
    v267 = (int *)sub_552200((_DWORD *)v830 + 30, 9);
    rf_geomod_face_corner_append(i, *v267, 1.349539, 1.814075, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v268 = (int *)sub_552200((_DWORD *)v830 + 30, 31);
    rf_geomod_face_corner_append(i, *v268, 0.90549701, 0.749668, 0.0, 0.0);
    v269 = (int *)sub_552200((_DWORD *)v830 + 30, 6);
    rf_geomod_face_corner_append(i, *v269, 1.531736, 0.392676, 0.0, 0.0);
    v270 = (int *)sub_552200((_DWORD *)v830 + 30, 33);
    rf_geomod_face_corner_append(i, *v270, 1.5533381, 0.133463, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v271 = (int *)sub_552200((_DWORD *)v830 + 30, 22);
    rf_geomod_face_corner_append(i, *v271, 0.037328999, 0.72803199, 0.0, 0.0);
    v272 = (int *)sub_552200((_DWORD *)v830 + 30, 7);
    rf_geomod_face_corner_append(i, *v272, 0.100209, 0.77481103, 0.0, 0.0);
    v273 = (int *)sub_552200((_DWORD *)v830 + 30, 23);
    rf_geomod_face_corner_append(i, *v273, 0.196906, 0.533997, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v274 = (int *)sub_552200((_DWORD *)v830 + 30, 8);
    rf_geomod_face_corner_append(i, *v274, 0.20694201, 0.80808699, 0.0, 0.0);
    v275 = (int *)sub_552200((_DWORD *)v830 + 30, 21);
    rf_geomod_face_corner_append(i, *v275, 0.25959599, 1.2156841, 0.0, 0.0);
    v276 = (int *)sub_552200((_DWORD *)v830 + 30, 16);
    rf_geomod_face_corner_append(i, *v276, 0.28636, 0.81648099, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v277 = (int *)sub_552200((_DWORD *)v830 + 30, 29);
    rf_geomod_face_corner_append(i, *v277, 0.76729703, 0.106214, 0.0, 0.0);
    v278 = (int *)sub_552200((_DWORD *)v830 + 30, 13);
    rf_geomod_face_corner_append(i, *v278, 0.95012897, 0.47050601, 0.0, 0.0);
    v279 = (int *)sub_552200((_DWORD *)v830 + 30, 5);
    rf_geomod_face_corner_append(i, *v279, 1.114886, 0.28675199, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v280 = (int *)sub_552200((_DWORD *)v830 + 30, 32);
    rf_geomod_face_corner_append(i, *v280, 1.076951, 0.85123903, 0.0, 0.0);
    v281 = (int *)sub_552200((_DWORD *)v830 + 30, 6);
    rf_geomod_face_corner_append(i, *v281, 1.531736, 0.392676, 0.0, 0.0);
    v282 = (int *)sub_552200((_DWORD *)v830 + 30, 31);
    rf_geomod_face_corner_append(i, *v282, 0.90549701, 0.749668, 0.0, 0.0);
    i = (float *)rf_solid_face_allocate_link(v830, v831);
    v283 = (int *)sub_552200((_DWORD *)v830 + 30, 1);
    rf_geomod_face_corner_append(i, *v283, 0.53207499, 0.49213001, 0.0, 0.0);
    v284 = (int *)sub_552200((_DWORD *)v830 + 30, 10);
    rf_geomod_face_corner_append(i, *v284, 0.324633, 0.57968301, 0.0, 0.0);
    v285 = (int *)sub_552200((_DWORD *)v830 + 30, 25);
    rf_geomod_face_corner_append(i, *v285, 0.39742699, 0.78181797, 0.0, 0.0);
    rf_solid_finalize_bounds((float *)v830);
    v718 = operator new(0x1CCu);
    v838 = 3;
    if ( v718 )
      v609 = (int *)rf_room460_construct_register(v718, v830, (const float *)v830 + 18, (const float *)v830 + 21);
    else
      v609 = nullptr;
    v719 = v609;
    v838 = -1;
    v827 = (float *)v609;
    for ( i = (float *)rf_receiver_get_first_dword((char *)v830 + 112); i; i = (float *)rf_solid_face_next_link((int)i) )
    {
      rf_geomod_face_finalize_geometry((int)i, nullptr, 0);
      rf_geomod_room_face_attach(v827, (int)i);
    }
    rf_room_face_spatial_tree_rebuild((int *)v827);
    return v830;
  }
  else if ( !_stricmp(String1, "bit_driller_single.v3d") )
  {
    strcpy(v820, "bit_driller_single.v3d");
    v716 = operator new(0x378u);
    v838 = 4;
    if ( v716 )
      v608 = rf_solid888_construct((void **)v716);
    else
      v608 = nullptr;
    v717 = v608;
    v838 = -1;
    v824 = v608;
    rf_vector3_default_construct_noop(v823);
    v286 = rf_vector3_set_components_return_destination(v715, 2.9000821, 1.0566339, 0.64954799);
    rf_vector_copy(v823, v714, v286);
    rf_solid_vertex_copy_append(v824, v823);
    v287 = rf_vector3_set_components_return_destination(v713, 0.68142498, 0.40995899, 2.495687);
    rf_vector_copy(v823, v712, v287);
    rf_solid_vertex_copy_append(v824, v823);
    v288 = rf_vector3_set_components_return_destination(v711, -2.0116341, 2.841331, -2.495687);
    rf_vector_copy(v823, v710, v288);
    rf_solid_vertex_copy_append(v824, v823);
    v289 = rf_vector3_set_components_return_destination(v709, -2.5982909, -2.556031, 0.64954799);
    rf_vector_copy(v823, v708, v289);
    rf_solid_vertex_copy_append(v824, v823);
    v290 = rf_vector3_set_components_return_destination(v707, 2.467658, -2.841331, 0.64954901);
    rf_vector_copy(v823, v706, v290);
    rf_solid_vertex_copy_append(v824, v823);
    v291 = rf_vector3_set_components_return_destination(v705, 1.446746, 2.7043331, 0.64954799);
    rf_vector_copy(v823, v704, v291);
    rf_solid_vertex_copy_append(v824, v823);
    v292 = rf_vector3_set_components_return_destination(v703, -1.857813, -2.539526, -2.495687);
    rf_vector_copy(v823, v702, v292);
    rf_solid_vertex_copy_append(v824, v823);
    v293 = rf_vector3_set_components_return_destination(v701, -0.65916902, -1.122092, 2.495687);
    rf_vector_copy(v823, v700, v293);
    rf_solid_vertex_copy_append(v824, v823);
    v294 = rf_vector3_set_components_return_destination(v699, 0.52468503, -1.144425, 2.495687);
    rf_vector_copy(v823, v698, v294);
    rf_solid_vertex_copy_append(v824, v823);
    v295 = rf_vector3_set_components_return_destination(v697, 2.150563, 2.041306, -2.495687);
    rf_vector_copy(v823, v696, v295);
    rf_solid_vertex_copy_append(v824, v823);
    v296 = rf_vector3_set_components_return_destination(v695, -2.587774, 2.5636201, 0.64954799);
    rf_vector_copy(v823, v694, v296);
    rf_solid_vertex_copy_append(v824, v823);
    v297 = rf_vector3_set_components_return_destination(v693, -0.71061403, 0.677526, 2.495687);
    rf_vector_copy(v823, v692, v297);
    rf_solid_vertex_copy_append(v824, v823);
    v298 = rf_vector3_set_components_return_destination(v691, 2.8482599, -0.58614999, -2.495687);
    rf_vector_copy(v823, v690, v298);
    rf_solid_vertex_copy_append(v824, v823);
    v299 = rf_vector3_set_components_return_destination(v689, -2.9000821, -0.96677202, -2.495687);
    rf_vector_copy(v823, v688, v299);
    rf_solid_vertex_copy_append(v824, v823);
    v300 = rf_vector3_set_components_return_destination(v687, 1.681911, -2.606302, -2.495687);
    rf_vector_copy(v823, v686, v300);
    rf_solid_vertex_copy_append(v824, v823);
    rf_geomod_face_metadata_init(v825);
    v825[2] = -1;
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v301 = (int *)sub_552200((_DWORD *)v824 + 30, 4);
    rf_geomod_face_corner_append(j, *v301, 0.56838, 0.72284299, 0.0, 0.0);
    v302 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v302, 0.955028, 0.39127201, 0.0, 0.0);
    v303 = (int *)sub_552200((_DWORD *)v824 + 30, 8);
    rf_geomod_face_corner_append(j, *v303, 0.56586599, 0.295109, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v304 = (int *)sub_552200((_DWORD *)v824 + 30, 9);
    rf_geomod_face_corner_append(j, *v304, 1.287028, 0.82631397, 0.0, 0.0);
    v305 = (int *)sub_552200((_DWORD *)v824 + 30, 10);
    rf_geomod_face_corner_append(j, *v305, 1.215228, 0.12960701, 0.0, 0.0);
    v306 = (int *)sub_552200((_DWORD *)v824 + 30, 2);
    rf_geomod_face_corner_append(j, *v306, 0.92783302, 0.52491301, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v307 = (int *)sub_552200((_DWORD *)v824 + 30, 14);
    rf_geomod_face_corner_append(j, *v307, 0.38977301, 0.53588402, 0.0, 0.0);
    v308 = (int *)sub_552200((_DWORD *)v824 + 30, 4);
    rf_geomod_face_corner_append(j, *v308, 0.43162, 0.92221802, 0.0, 0.0);
    v309 = (int *)sub_552200((_DWORD *)v824 + 30, 12);
    rf_geomod_face_corner_append(j, *v309, 0.676943, 0.49949199, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v310 = (int *)sub_552200((_DWORD *)v824 + 30, 8);
    rf_geomod_face_corner_append(j, *v310, 0.56586599, 0.295109, 0.0, 0.0);
    v311 = (int *)sub_552200((_DWORD *)v824 + 30, 1);
    rf_geomod_face_corner_append(j, *v311, 0.40540099, 0.225271, 0.0, 0.0);
    v312 = (int *)sub_552200((_DWORD *)v824 + 30, 0);
    rf_geomod_face_corner_append(j, *v312, 0.162763, 0.55017197, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v313 = (int *)sub_552200((_DWORD *)v824 + 30, 11);
    rf_geomod_face_corner_append(j, *v313, 0.49367401, 0.65431601, 0.0, 0.0);
    v314 = (int *)sub_552200((_DWORD *)v824 + 30, 7);
    rf_geomod_face_corner_append(j, *v314, 0.66043299, 0.76804298, 0.0, 0.0);
    v315 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v315, 0.955028, 0.52706802, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v316 = (int *)sub_552200((_DWORD *)v824 + 30, 2);
    rf_geomod_face_corner_append(j, *v316, 0.394375, 0.92783302, 0.0, 0.0);
    v317 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v317, 0.955028, 1.527068, 0.0, 0.0);
    v318 = (int *)sub_552200((_DWORD *)v824 + 30, 13);
    rf_geomod_face_corner_append(j, *v318, 0.82870001, 1.094125, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v319 = (int *)sub_552200((_DWORD *)v824 + 30, 1);
    rf_geomod_face_corner_append(j, *v319, 0.40540099, 0.77444798, 0.0, 0.0);
    v320 = (int *)sub_552200((_DWORD *)v824 + 30, 8);
    rf_geomod_face_corner_append(j, *v320, 0.56586599, 0.85767698, 0.0, 0.0);
    v321 = (int *)sub_552200((_DWORD *)v824 + 30, 7);
    rf_geomod_face_corner_append(j, *v321, 0.66043299, 0.76804298, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v322 = (int *)sub_552200((_DWORD *)v824 + 30, 13);
    rf_geomod_face_corner_append(j, *v322, 0.90587503, 0.66444898, 0.0, 0.0);
    v323 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v323, 0.47293201, 0.39127201, 0.0, 0.0);
    v324 = (int *)sub_552200((_DWORD *)v824 + 30, 6);
    rf_geomod_face_corner_append(j, *v324, 0.73212302, 0.81024402, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v325 = (int *)sub_552200((_DWORD *)v824 + 30, 4);
    rf_geomod_face_corner_append(j, *v325, 0.077781998, 0.72284299, 0.0, 0.0);
    v326 = (int *)sub_552200((_DWORD *)v824 + 30, 14);
    rf_geomod_face_corner_append(j, *v326, 0.46411601, 1.035129, 0.0, 0.0);
    v327 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v327, 0.47293201, 0.39127201, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v328 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v328, 0.044971999, 0.39127201, 0.0, 0.0);
    v329 = (int *)sub_552200((_DWORD *)v824 + 30, 2);
    rf_geomod_face_corner_append(j, *v329, 0.60562497, 0.52491301, 0.0, 0.0);
    v330 = (int *)sub_552200((_DWORD *)v824 + 30, 10);
    rf_geomod_face_corner_append(j, *v330, 0.532188, 0.12960701, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v331 = (int *)sub_552200((_DWORD *)v824 + 30, 0);
    rf_geomod_face_corner_append(j, *v331, 0.162763, 0.55017197, 0.0, 0.0);
    v332 = (int *)sub_552200((_DWORD *)v824 + 30, 4);
    rf_geomod_face_corner_append(j, *v332, 0.56838, 0.72284299, 0.0, 0.0);
    v333 = (int *)sub_552200((_DWORD *)v824 + 30, 8);
    rf_geomod_face_corner_append(j, *v333, 0.56586599, 0.295109, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v334 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v334, 0.955028, 0.52706802, 0.0, 0.0);
    v335 = (int *)sub_552200((_DWORD *)v824 + 30, 10);
    rf_geomod_face_corner_append(j, *v335, 0.467812, 0.21522801, 0.0, 0.0);
    v336 = (int *)sub_552200((_DWORD *)v824 + 30, 11);
    rf_geomod_face_corner_append(j, *v336, 0.49367401, 0.65431601, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v337 = (int *)sub_552200((_DWORD *)v824 + 30, 10);
    rf_geomod_face_corner_append(j, *v337, 0.21522801, 0.12960701, 0.0, 0.0);
    v338 = (int *)sub_552200((_DWORD *)v824 + 30, 9);
    rf_geomod_face_corner_append(j, *v338, 0.28702801, 0.82631397, 0.0, 0.0);
    v339 = (int *)sub_552200((_DWORD *)v824 + 30, 5);
    rf_geomod_face_corner_append(j, *v339, 0.50745797, 0.374818, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v340 = (int *)sub_552200((_DWORD *)v824 + 30, 10);
    rf_geomod_face_corner_append(j, *v340, 0.467812, 0.21522801, 0.0, 0.0);
    v341 = (int *)sub_552200((_DWORD *)v824 + 30, 5);
    rf_geomod_face_corner_append(j, *v341, 0.124934, 0.50745797, 0.0, 0.0);
    v342 = (int *)sub_552200((_DWORD *)v824 + 30, 1);
    rf_geomod_face_corner_append(j, *v342, 0.40540099, 0.77444798, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v343 = (int *)sub_552200((_DWORD *)v824 + 30, 1);
    rf_geomod_face_corner_append(j, *v343, 0.77444798, 0.225271, 0.0, 0.0);
    v344 = (int *)sub_552200((_DWORD *)v824 + 30, 11);
    rf_geomod_face_corner_append(j, *v344, 0.65431601, 0.124468, 0.0, 0.0);
    v345 = (int *)sub_552200((_DWORD *)v824 + 30, 10);
    rf_geomod_face_corner_append(j, *v345, 0.21522801, 0.12960701, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v346 = (int *)sub_552200((_DWORD *)v824 + 30, 12);
    rf_geomod_face_corner_append(j, *v346, 0.49949199, 1.0045919, 0.0, 0.0);
    v347 = (int *)sub_552200((_DWORD *)v824 + 30, 0);
    rf_geomod_face_corner_append(j, *v347, 0.71643603, 0.55017197, 0.0, 0.0);
    v348 = (int *)sub_552200((_DWORD *)v824 + 30, 9);
    rf_geomod_face_corner_append(j, *v348, 0.28702801, 0.82631397, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v349 = (int *)sub_552200((_DWORD *)v824 + 30, 1);
    rf_geomod_face_corner_append(j, *v349, 0.40540099, 0.77444798, 0.0, 0.0);
    v350 = (int *)sub_552200((_DWORD *)v824 + 30, 7);
    rf_geomod_face_corner_append(j, *v350, 0.66043299, 0.76804298, 0.0, 0.0);
    v351 = (int *)sub_552200((_DWORD *)v824 + 30, 11);
    rf_geomod_face_corner_append(j, *v351, 0.49367401, 0.65431601, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v352 = (int *)sub_552200((_DWORD *)v824 + 30, 5);
    rf_geomod_face_corner_append(j, *v352, 0.50745797, 0.374818, 0.0, 0.0);
    v353 = (int *)sub_552200((_DWORD *)v824 + 30, 9);
    rf_geomod_face_corner_append(j, *v353, 0.28702801, 0.82631397, 0.0, 0.0);
    v354 = (int *)sub_552200((_DWORD *)v824 + 30, 0);
    rf_geomod_face_corner_append(j, *v354, 0.71643603, 0.55017197, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v355 = (int *)sub_552200((_DWORD *)v824 + 30, 5);
    rf_geomod_face_corner_append(j, *v355, 0.50745797, 0.374818, 0.0, 0.0);
    v356 = (int *)sub_552200((_DWORD *)v824 + 30, 0);
    rf_geomod_face_corner_append(j, *v356, 0.71643603, 0.55017197, 0.0, 0.0);
    v357 = (int *)sub_552200((_DWORD *)v824 + 30, 1);
    rf_geomod_face_corner_append(j, *v357, 0.77444798, 0.225271, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v358 = (int *)sub_552200((_DWORD *)v824 + 30, 7);
    rf_geomod_face_corner_append(j, *v358, 0.66043299, 0.219896, 0.0, 0.0);
    v359 = (int *)sub_552200((_DWORD *)v824 + 30, 8);
    rf_geomod_face_corner_append(j, *v359, 0.56586599, 0.295109, 0.0, 0.0);
    v360 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v360, 0.955028, 0.39127201, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v361 = (int *)sub_552200((_DWORD *)v824 + 30, 0);
    rf_geomod_face_corner_append(j, *v361, 0.162763, 0.55017197, 0.0, 0.0);
    v362 = (int *)sub_552200((_DWORD *)v824 + 30, 12);
    rf_geomod_face_corner_append(j, *v362, 0.323057, 1.0045919, 0.0, 0.0);
    v363 = (int *)sub_552200((_DWORD *)v824 + 30, 4);
    rf_geomod_face_corner_append(j, *v363, 0.56838, 0.72284299, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v364 = (int *)sub_552200((_DWORD *)v824 + 30, 6);
    rf_geomod_face_corner_append(j, *v364, 0.73212302, 0.81024402, 0.0, 0.0);
    v365 = (int *)sub_552200((_DWORD *)v824 + 30, 3);
    rf_geomod_face_corner_append(j, *v365, 0.47293201, 0.39127201, 0.0, 0.0);
    v366 = (int *)sub_552200((_DWORD *)v824 + 30, 14);
    rf_geomod_face_corner_append(j, *v366, 0.46411601, 1.035129, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v367 = (int *)sub_552200((_DWORD *)v824 + 30, 13);
    rf_geomod_face_corner_append(j, *v367, 0.17129999, 1.094125, 0.0, 0.0);
    v368 = (int *)sub_552200((_DWORD *)v824 + 30, 6);
    rf_geomod_face_corner_append(j, *v368, 0.107017, 1.267877, 0.0, 0.0);
    v369 = (int *)sub_552200((_DWORD *)v824 + 30, 2);
    rf_geomod_face_corner_append(j, *v369, 0.60562497, 0.92783302, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v370 = (int *)sub_552200((_DWORD *)v824 + 30, 6);
    rf_geomod_face_corner_append(j, *v370, 0.107017, 1.267877, 0.0, 0.0);
    v371 = (int *)sub_552200((_DWORD *)v824 + 30, 14);
    rf_geomod_face_corner_append(j, *v371, 0.38977301, 1.535884, 0.0, 0.0);
    v372 = (int *)sub_552200((_DWORD *)v824 + 30, 2);
    rf_geomod_face_corner_append(j, *v372, 0.60562497, 0.92783302, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v373 = (int *)sub_552200((_DWORD *)v824 + 30, 14);
    rf_geomod_face_corner_append(j, *v373, 0.38977301, 1.535884, 0.0, 0.0);
    v374 = (int *)sub_552200((_DWORD *)v824 + 30, 12);
    rf_geomod_face_corner_append(j, *v374, 0.676943, 1.499492, 0.0, 0.0);
    v375 = (int *)sub_552200((_DWORD *)v824 + 30, 2);
    rf_geomod_face_corner_append(j, *v375, 0.60562497, 0.92783302, 0.0, 0.0);
    j = (float *)rf_solid_face_allocate_link(v824, v825);
    v376 = (int *)sub_552200((_DWORD *)v824 + 30, 2);
    rf_geomod_face_corner_append(j, *v376, 0.60562497, 0.92783302, 0.0, 0.0);
    v377 = (int *)sub_552200((_DWORD *)v824 + 30, 12);
    rf_geomod_face_corner_append(j, *v377, 0.676943, 1.499492, 0.0, 0.0);
    v378 = (int *)sub_552200((_DWORD *)v824 + 30, 9);
    rf_geomod_face_corner_append(j, *v378, 0.86956298, 1.287028, 0.0, 0.0);
    rf_solid_finalize_bounds((float *)v824);
    v684 = operator new(0x1CCu);
    v838 = 5;
    if ( v684 )
      v607 = (int *)rf_room460_construct_register(v684, v824, (const float *)v824 + 18, (const float *)v824 + 21);
    else
      v607 = nullptr;
    v685 = v607;
    v838 = -1;
    v821 = (float *)v607;
    for ( j = (float *)rf_receiver_get_first_dword((char *)v824 + 112); j; j = (float *)rf_solid_face_next_link((int)j) )
    {
      rf_geomod_face_finalize_geometry((int)j, nullptr, 0);
      rf_geomod_room_face_attach(v821, (int)j);
    }
    rf_room_face_spatial_tree_rebuild((int *)v821);
    return v824;
  }
  else if ( !_stricmp(String1, "Holey_APC.v3d") )
  {
    strcpy(v814, "Holey_APC.v3d");
    v682 = operator new(0x378u);
    v838 = 6;
    if ( v682 )
      v606 = rf_solid888_construct((void **)v682);
    else
      v606 = nullptr;
    v683 = v606;
    v838 = -1;
    v818 = v606;
    rf_vector3_default_construct_noop(v817);
    v379 = rf_vector3_set_components_return_destination(v681, -1.5843689, 2.0916231, -0.39987999);
    rf_vector_copy(v817, v680, v379);
    rf_solid_vertex_copy_append(v818, v817);
    v380 = rf_vector3_set_components_return_destination(v679, 0.967843, -1.6123739, 0.76569098);
    rf_vector_copy(v817, v678, v380);
    rf_solid_vertex_copy_append(v818, v817);
    v381 = rf_vector3_set_components_return_destination(v677, -1.808267, 1.96365, -0.76569098);
    rf_vector_copy(v817, v676, v381);
    rf_solid_vertex_copy_append(v818, v817);
    v382 = rf_vector3_set_components_return_destination(v675, -0.69153798, 1.937272, -0.76569098);
    rf_vector_copy(v817, v674, v382);
    rf_solid_vertex_copy_append(v818, v817);
    v383 = rf_vector3_set_components_return_destination(v673, -2.3943291, -1.733085, 0.21667901);
    rf_vector_copy(v817, v672, v383);
    rf_solid_vertex_copy_append(v818, v817);
    v384 = rf_vector3_set_components_return_destination(v671, -2.5973549, -1.14696, 0.21667901);
    rf_vector_copy(v817, v670, v384);
    rf_solid_vertex_copy_append(v818, v817);
    v385 = rf_vector3_set_components_return_destination(v669, -1.365647, 1.415964, 0.76569098);
    rf_vector_copy(v817, v668, v385);
    rf_solid_vertex_copy_append(v818, v817);
    v386 = rf_vector3_set_components_return_destination(v667, 2.670594, -0.64613599, 0.21667901);
    rf_vector_copy(v817, v666, v386);
    rf_solid_vertex_copy_append(v818, v817);
    v387 = rf_vector3_set_components_return_destination(v665, 2.5752449, -1.221666, 0.21667901);
    rf_vector_copy(v817, v664, v387);
    rf_solid_vertex_copy_append(v818, v817);
    v388 = rf_vector3_set_components_return_destination(v663, 1.531925, 1.917138, -0.76569098);
    rf_vector_copy(v817, v662, v388);
    rf_solid_vertex_copy_append(v818, v817);
    v389 = rf_vector3_set_components_return_destination(v661, 1.929142, -1.166783, 0.76569098);
    rf_vector_copy(v817, v660, v389);
    rf_solid_vertex_copy_append(v818, v817);
    v390 = rf_vector3_set_components_return_destination(v659, -2.2932241, 1.7299139, 0.21667799);
    rf_vector_copy(v817, v658, v390);
    rf_solid_vertex_copy_append(v818, v817);
    v391 = rf_vector3_set_components_return_destination(v657, 2.0416739, 1.7142, -0.76569098);
    rf_vector_copy(v817, v656, v391);
    rf_solid_vertex_copy_append(v818, v817);
    v392 = rf_vector3_set_components_return_destination(v655, -1.995083, -0.83858597, 0.76569098);
    rf_vector_copy(v817, v654, v392);
    rf_solid_vertex_copy_append(v818, v817);
    v393 = rf_vector3_set_components_return_destination(v653, 1.949423, 1.928273, -0.39987901);
    rf_vector_copy(v817, v652, v393);
    rf_solid_vertex_copy_append(v818, v817);
    v394 = rf_vector3_set_components_return_destination(v651, -2.420213, 1.364462, -0.76569098);
    rf_vector_copy(v817, v650, v394);
    rf_solid_vertex_copy_append(v818, v817);
    v395 = rf_vector3_set_components_return_destination(v649, 2.440058, -1.65663, 0.21667901);
    rf_vector_copy(v817, v648, v395);
    rf_solid_vertex_copy_append(v818, v817);
    v396 = rf_vector3_set_components_return_destination(v647, -1.812323, 1.021839, 0.76569098);
    rf_vector_copy(v817, v646, v396);
    rf_solid_vertex_copy_append(v818, v817);
    v397 = rf_vector3_set_components_return_destination(v645, 2.6595459, -0.53017598, -0.76569098);
    rf_vector_copy(v817, v644, v397);
    rf_solid_vertex_copy_append(v818, v817);
    v398 = rf_vector3_set_components_return_destination(v643, -1.274352, -1.431147, 0.76569098);
    rf_vector_copy(v817, v642, v398);
    rf_solid_vertex_copy_append(v818, v817);
    v399 = rf_vector3_set_components_return_destination(v641, -2.2932241, 1.729913, -0.39987999);
    rf_vector_copy(v817, v640, v399);
    rf_solid_vertex_copy_append(v818, v817);
    v400 = rf_vector3_set_components_return_destination(v639, 2.534761, -1.602541, -0.76569098);
    rf_vector_copy(v817, v638, v400);
    rf_solid_vertex_copy_append(v818, v817);
    v401 = rf_vector3_set_components_return_destination(v637, 2.6201029, -0.17111801, 0.21667799);
    rf_vector_copy(v817, v636, v401);
    rf_solid_vertex_copy_append(v818, v817);
    v402 = rf_vector3_set_components_return_destination(v635, 2.020226, -0.448704, 0.76569098);
    rf_vector_copy(v817, v634, v402);
    rf_solid_vertex_copy_append(v818, v817);
    v403 = rf_vector3_set_components_return_destination(v633, 1.462273, -2.0916231, -0.76569098);
    rf_vector_copy(v817, v632, v403);
    rf_solid_vertex_copy_append(v818, v817);
    v404 = rf_vector3_set_components_return_destination(v631, 2.1378901, -2.0278981, 0.21667901);
    rf_vector_copy(v817, v630, v404);
    rf_solid_vertex_copy_append(v818, v817);
    v405 = rf_vector3_set_components_return_destination(v629, -1.70464, -2.079653, 0.21667901);
    rf_vector_copy(v817, v628, v405);
    rf_solid_vertex_copy_append(v818, v817);
    v406 = rf_vector3_set_components_return_destination(v627, -2.1297591, -2.083674, -0.76569098);
    rf_vector_copy(v817, v626, v406);
    rf_solid_vertex_copy_append(v818, v817);
    v407 = rf_vector3_set_components_return_destination(v625, -2.3943291, -1.733085, -0.39987999);
    rf_vector_copy(v817, v624, v407);
    rf_solid_vertex_copy_append(v818, v817);
    v408 = rf_vector3_set_components_return_destination(v623, -2.4561, 1.2674069, 0.21667799);
    rf_vector_copy(v817, v622, v408);
    rf_solid_vertex_copy_append(v818, v817);
    v409 = rf_vector3_set_components_return_destination(v621, -2.670594, -1.064314, -0.76569098);
    rf_vector_copy(v817, v620, v409);
    rf_solid_vertex_copy_append(v818, v817);
    v410 = rf_vector3_set_components_return_destination(v619, 1.949423, 1.928274, 0.21667799);
    rf_vector_copy(v817, v618, v410);
    rf_solid_vertex_copy_append(v818, v817);
    v411 = rf_vector3_set_components_return_destination(v617, 1.569224, 1.233884, 0.76569098);
    rf_vector_copy(v817, v616, v411);
    rf_solid_vertex_copy_append(v818, v817);
    v412 = rf_vector3_set_components_return_destination(v615, -1.913378, 2.0322471, 0.21667799);
    rf_vector_copy(v817, v614, v412);
    rf_solid_vertex_copy_append(v818, v817);
    rf_geomod_face_metadata_init(v819);
    v819[2] = -1;
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v413 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v413, 1.944271, 1.844795, 0.0, 0.0);
    v414 = (int *)sub_552200((_DWORD *)v818 + 30, 0);
    rf_geomod_face_corner_append(k, *v414, 1.5239739, 0.863684, 0.0, 0.0);
    v415 = (int *)sub_552200((_DWORD *)v818 + 30, 3);
    rf_geomod_face_corner_append(k, *v415, 0.38341501, 0.28157699, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v416 = (int *)sub_552200((_DWORD *)v818 + 30, 12);
    rf_geomod_face_corner_append(k, *v416, 0.89183599, 0.28157601, 0.0, 0.0);
    v417 = (int *)sub_552200((_DWORD *)v818 + 30, 14);
    rf_geomod_face_corner_append(k, *v417, 1.0096821, 0.86368197, 0.0, 0.0);
    v418 = (int *)sub_552200((_DWORD *)v818 + 30, 9);
    rf_geomod_face_corner_append(k, *v418, 1.543022, 0.28157601, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v419 = (int *)sub_552200((_DWORD *)v818 + 30, 17);
    rf_geomod_face_corner_append(k, *v419, 0.81517702, 1.833308, 0.0, 0.0);
    v420 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v420, 0.94427103, 0.18526, 0.0, 0.0);
    v421 = (int *)sub_552200((_DWORD *)v818 + 30, 6);
    rf_geomod_face_corner_append(k, *v421, 0.244564, 1.19046, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v422 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v422, 4.9442711, 1.844795, 0.0, 0.0);
    v423 = (int *)sub_552200((_DWORD *)v818 + 30, 9);
    rf_geomod_face_corner_append(k, *v423, 0.54302198, 0.28157601, 0.0, 0.0);
    v424 = (int *)sub_552200((_DWORD *)v818 + 30, 31);
    rf_geomod_face_corner_append(k, *v424, 0.0096819997, 1.844793, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v425 = (int *)sub_552200((_DWORD *)v818 + 30, 31);
    rf_geomod_face_corner_append(k, *v425, 0.0096819997, 1.844793, 0.0, 0.0);
    v426 = (int *)sub_552200((_DWORD *)v818 + 30, 9);
    rf_geomod_face_corner_append(k, *v426, 0.54302198, 0.28157601, 0.0, 0.0);
    v427 = (int *)sub_552200((_DWORD *)v818 + 30, 14);
    rf_geomod_face_corner_append(k, *v427, 0.0096819997, 0.86368197, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v428 = (int *)sub_552200((_DWORD *)v818 + 30, 4);
    rf_geomod_face_corner_append(k, *v428, 0.155204, 0.32678601, 0.0, 0.0);
    v429 = (int *)sub_552200((_DWORD *)v818 + 30, 27);
    rf_geomod_face_corner_append(k, *v429, 1.7184221, 0.89862299, 0.0, 0.0);
    v430 = (int *)sub_552200((_DWORD *)v818 + 30, 28);
    rf_geomod_face_corner_append(k, *v430, 1.1363159, 0.32678699, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v431 = (int *)sub_552200((_DWORD *)v818 + 30, 25);
    rf_geomod_face_corner_append(k, *v431, 1.231077, 1.844794, 0.0, 0.0);
    v432 = (int *)sub_552200((_DWORD *)v818 + 30, 21);
    rf_geomod_face_corner_append(k, *v432, 1.738066, 0.28157499, 0.0, 0.0);
    v433 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v433, 0.36800101, 0.28157601, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v434 = (int *)sub_552200((_DWORD *)v818 + 30, 13);
    rf_geomod_face_corner_append(k, *v434, 1.048647, 0.86779398, 0.0, 0.0);
    v435 = (int *)sub_552200((_DWORD *)v818 + 30, 19);
    rf_geomod_face_corner_append(k, *v435, 0.127939, 1.834304, 0.0, 0.0);
    v436 = (int *)sub_552200((_DWORD *)v818 + 30, 5);
    rf_geomod_face_corner_append(k, *v436, 1.818027, 1.370774, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v437 = (int *)sub_552200((_DWORD *)v818 + 30, 31);
    rf_geomod_face_corner_append(k, *v437, 1.844793, 0.354846, 0.0, 0.0);
    v438 = (int *)sub_552200((_DWORD *)v818 + 30, 12);
    rf_geomod_face_corner_append(k, *v438, 0.28157601, 0.70401597, 0.0, 0.0);
    v439 = (int *)sub_552200((_DWORD *)v818 + 30, 22);
    rf_geomod_face_corner_append(k, *v439, 1.844793, 3.7791049, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v440 = (int *)sub_552200((_DWORD *)v818 + 30, 19);
    rf_geomod_face_corner_append(k, *v440, 3.127939, 0.83430398, 0.0, 0.0);
    v441 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v441, 0.263616, 1.129898, 0.0, 0.0);
    v442 = (int *)sub_552200((_DWORD *)v818 + 30, 26);
    rf_geomod_face_corner_append(k, *v442, 3.6776159, 1.892063, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v443 = (int *)sub_552200((_DWORD *)v818 + 30, 11);
    rf_geomod_face_corner_append(k, *v443, 1.429511, 0.67838597, 0.0, 0.0);
    v444 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v444, 0.94427103, 0.18526, 0.0, 0.0);
    v445 = (int *)sub_552200((_DWORD *)v818 + 30, 17);
    rf_geomod_face_corner_append(k, *v445, 0.81517702, 1.833308, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v446 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v446, 0.71842098, 0.235973, 0.0, 0.0);
    v447 = (int *)sub_552200((_DWORD *)v818 + 30, 28);
    rf_geomod_face_corner_append(k, *v447, 0.136316, 1.326787, 0.0, 0.0);
    v448 = (int *)sub_552200((_DWORD *)v818 + 30, 27);
    rf_geomod_face_corner_append(k, *v448, 0.718422, 1.898623, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v449 = (int *)sub_552200((_DWORD *)v818 + 30, 8);
    rf_geomod_face_corner_append(k, *v449, 1.844793, 1.492626, 0.0, 0.0);
    v450 = (int *)sub_552200((_DWORD *)v818 + 30, 18);
    rf_geomod_face_corner_append(k, *v450, 0.28157499, 0.364755, 0.0, 0.0);
    v451 = (int *)sub_552200((_DWORD *)v818 + 30, 21);
    rf_geomod_face_corner_append(k, *v451, 0.28157499, 2.1138599, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v452 = (int *)sub_552200((_DWORD *)v818 + 30, 7);
    rf_geomod_face_corner_append(k, *v452, 1.844793, 0.55389398, 0.0, 0.0);
    v453 = (int *)sub_552200((_DWORD *)v818 + 30, 18);
    rf_geomod_face_corner_append(k, *v453, 0.28157499, 0.364755, 0.0, 0.0);
    v454 = (int *)sub_552200((_DWORD *)v818 + 30, 8);
    rf_geomod_face_corner_append(k, *v454, 1.844793, 1.492626, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v455 = (int *)sub_552200((_DWORD *)v818 + 30, 8);
    rf_geomod_face_corner_append(k, *v455, 0.210217, 0.49262601, 0.0, 0.0);
    v456 = (int *)sub_552200((_DWORD *)v818 + 30, 16);
    rf_geomod_face_corner_append(k, *v456, 0.38291401, 1.202083, 0.0, 0.0);
    v457 = (int *)sub_552200((_DWORD *)v818 + 30, 10);
    rf_geomod_face_corner_append(k, *v457, 1.035591, 0.403108, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v458 = (int *)sub_552200((_DWORD *)v818 + 30, 16);
    rf_geomod_face_corner_append(k, *v458, 0.61708599, 1.844793, 0.0, 0.0);
    v459 = (int *)sub_552200((_DWORD *)v818 + 30, 21);
    rf_geomod_face_corner_append(k, *v459, 0.73806602, 0.28157499, 0.0, 0.0);
    v460 = (int *)sub_552200((_DWORD *)v818 + 30, 25);
    rf_geomod_face_corner_append(k, *v460, 0.231077, 1.844794, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v461 = (int *)sub_552200((_DWORD *)v818 + 30, 26);
    rf_geomod_face_corner_append(k, *v461, 1.322384, 1.8447959, 0.0, 0.0);
    v462 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v462, 5.368001, 0.28157601, 0.0, 0.0);
    v463 = (int *)sub_552200((_DWORD *)v818 + 30, 27);
    rf_geomod_face_corner_append(k, *v463, 0.77930897, 0.281578, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v464 = (int *)sub_552200((_DWORD *)v818 + 30, 25);
    rf_geomod_face_corner_append(k, *v464, 5.2310772, 1.844794, 0.0, 0.0);
    v465 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v465, 4.368001, 0.28157601, 0.0, 0.0);
    v466 = (int *)sub_552200((_DWORD *)v818 + 30, 26);
    rf_geomod_face_corner_append(k, *v466, 0.322384, 1.8447959, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v467 = (int *)sub_552200((_DWORD *)v818 + 30, 5);
    rf_geomod_face_corner_append(k, *v467, 0.155203, 0.370774, 0.0, 0.0);
    v468 = (int *)sub_552200((_DWORD *)v818 + 30, 28);
    rf_geomod_face_corner_append(k, *v468, 1.1363159, 1.326787, 0.0, 0.0);
    v469 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v469, 1.718421, 0.235973, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v470 = (int *)sub_552200((_DWORD *)v818 + 30, 4);
    rf_geomod_face_corner_append(k, *v470, 0.155204, 1.326786, 0.0, 0.0);
    v471 = (int *)sub_552200((_DWORD *)v818 + 30, 28);
    rf_geomod_face_corner_append(k, *v471, 1.1363159, 1.326787, 0.0, 0.0);
    v472 = (int *)sub_552200((_DWORD *)v818 + 30, 5);
    rf_geomod_face_corner_append(k, *v472, 0.155203, 0.370774, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v473 = (int *)sub_552200((_DWORD *)v818 + 30, 11);
    rf_geomod_face_corner_append(k, *v473, 0.155204, 0.67838597, 0.0, 0.0);
    v474 = (int *)sub_552200((_DWORD *)v818 + 30, 15);
    rf_geomod_face_corner_append(k, *v474, 1.7184221, 1.274464, 0.0, 0.0);
    v475 = (int *)sub_552200((_DWORD *)v818 + 30, 20);
    rf_geomod_face_corner_append(k, *v475, 1.1363159, 0.67838699, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v476 = (int *)sub_552200((_DWORD *)v818 + 30, 31);
    rf_geomod_face_corner_append(k, *v476, 1.844793, 0.354846, 0.0, 0.0);
    v477 = (int *)sub_552200((_DWORD *)v818 + 30, 14);
    rf_geomod_face_corner_append(k, *v477, 0.86368197, 0.35484701, 0.0, 0.0);
    v478 = (int *)sub_552200((_DWORD *)v818 + 30, 12);
    rf_geomod_face_corner_append(k, *v478, 0.28157601, 0.70401597, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v479 = (int *)sub_552200((_DWORD *)v818 + 30, 29);
    rf_geomod_face_corner_append(k, *v479, 0.155204, 0.43276799, 0.0, 0.0);
    v480 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v480, 1.718421, 4.2359719, 0.0, 0.0);
    v481 = (int *)sub_552200((_DWORD *)v818 + 30, 15);
    rf_geomod_face_corner_append(k, *v481, 1.7184221, 0.27446401, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v482 = (int *)sub_552200((_DWORD *)v818 + 30, 5);
    rf_geomod_face_corner_append(k, *v482, 0.155203, 4.3707738, 0.0, 0.0);
    v483 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v483, 1.718421, 4.2359719, 0.0, 0.0);
    v484 = (int *)sub_552200((_DWORD *)v818 + 30, 29);
    rf_geomod_face_corner_append(k, *v484, 0.155204, 0.43276799, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v485 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v485, 0.94427103, 1.844795, 0.0, 0.0);
    v486 = (int *)sub_552200((_DWORD *)v818 + 30, 20);
    rf_geomod_face_corner_append(k, *v486, 1.429512, 0.863684, 0.0, 0.0);
    v487 = (int *)sub_552200((_DWORD *)v818 + 30, 2);
    rf_geomod_face_corner_append(k, *v487, 0.80999601, 0.281578, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v488 = (int *)sub_552200((_DWORD *)v818 + 30, 11);
    rf_geomod_face_corner_append(k, *v488, 1.429511, 1.8447959, 0.0, 0.0);
    v489 = (int *)sub_552200((_DWORD *)v818 + 30, 20);
    rf_geomod_face_corner_append(k, *v489, 1.429512, 0.863684, 0.0, 0.0);
    v490 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v490, 0.94427103, 1.844795, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v491 = (int *)sub_552200((_DWORD *)v818 + 30, 27);
    rf_geomod_face_corner_append(k, *v491, 0.77930897, 1.898623, 0.0, 0.0);
    v492 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v492, 5.368001, 1.911588, 0.0, 0.0);
    v493 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v493, 0.088412002, 0.235973, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v494 = (int *)sub_552200((_DWORD *)v818 + 30, 23);
    rf_geomod_face_corner_append(k, *v494, 0.91923499, 3.231869, 0.0, 0.0);
    v495 = (int *)sub_552200((_DWORD *)v818 + 30, 32);
    rf_geomod_face_corner_append(k, *v495, 1.495373, 0.48744699, 0.0, 0.0);
    v496 = (int *)sub_552200((_DWORD *)v818 + 30, 22);
    rf_geomod_face_corner_append(k, *v496, 0.152913, 2.7791049, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v497 = (int *)sub_552200((_DWORD *)v818 + 30, 15);
    rf_geomod_face_corner_append(k, *v497, 0.40826499, 1.274464, 0.0, 0.0);
    v498 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v498, 0.088412002, 5.2359719, 0.0, 0.0);
    v499 = (int *)sub_552200((_DWORD *)v818 + 30, 2);
    rf_geomod_face_corner_append(k, *v499, 1.190004, 0.297144, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v500 = (int *)sub_552200((_DWORD *)v818 + 30, 2);
    rf_geomod_face_corner_append(k, *v500, 1.190004, 0.297144, 0.0, 0.0);
    v501 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v501, 0.088412002, 5.2359719, 0.0, 0.0);
    v502 = (int *)sub_552200((_DWORD *)v818 + 30, 3);
    rf_geomod_face_corner_append(k, *v502, 2.616585, 0.34017, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v503 = (int *)sub_552200((_DWORD *)v818 + 30, 30);
    rf_geomod_face_corner_append(k, *v503, 0.088412002, 5.2359719, 0.0, 0.0);
    v504 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v504, 5.368001, 6.9115882, 0.0, 0.0);
    v505 = (int *)sub_552200((_DWORD *)v818 + 30, 3);
    rf_geomod_face_corner_append(k, *v505, 2.616585, 0.34017, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v506 = (int *)sub_552200((_DWORD *)v818 + 30, 3);
    rf_geomod_face_corner_append(k, *v506, 0.61658502, 0.34017, 0.0, 0.0);
    v507 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v507, 3.368001, 6.9115882, 0.0, 0.0);
    v508 = (int *)sub_552200((_DWORD *)v818 + 30, 9);
    rf_geomod_face_corner_append(k, *v508, 3.4569781, 0.37301001, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v509 = (int *)sub_552200((_DWORD *)v818 + 30, 17);
    rf_geomod_face_corner_append(k, *v509, 0.81517702, 0.83330798, 0.0, 0.0);
    v510 = (int *)sub_552200((_DWORD *)v818 + 30, 13);
    rf_geomod_face_corner_append(k, *v510, 1.048647, 3.867794, 0.0, 0.0);
    v511 = (int *)sub_552200((_DWORD *)v818 + 30, 29);
    rf_geomod_face_corner_append(k, *v511, 1.637579, 0.43276799, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v512 = (int *)sub_552200((_DWORD *)v818 + 30, 25);
    rf_geomod_face_corner_append(k, *v512, 0.76892298, 1.8076479, 0.0, 0.0);
    v513 = (int *)sub_552200((_DWORD *)v818 + 30, 10);
    rf_geomod_face_corner_append(k, *v513, 1.035591, 0.403108, 0.0, 0.0);
    v514 = (int *)sub_552200((_DWORD *)v818 + 30, 16);
    rf_geomod_face_corner_append(k, *v514, 0.38291401, 1.202083, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v515 = (int *)sub_552200((_DWORD *)v818 + 30, 9);
    rf_geomod_face_corner_append(k, *v515, 0.45697799, 0.37301001, 0.0, 0.0);
    v516 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v516, 0.36800101, 6.9115882, 0.0, 0.0);
    v517 = (int *)sub_552200((_DWORD *)v818 + 30, 12);
    rf_geomod_face_corner_append(k, *v517, 1.108164, 0.70401597, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v518 = (int *)sub_552200((_DWORD *)v818 + 30, 12);
    rf_geomod_face_corner_append(k, *v518, 1.108164, 0.70401597, 0.0, 0.0);
    v519 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v519, 0.36800101, 6.9115882, 0.0, 0.0);
    v520 = (int *)sub_552200((_DWORD *)v818 + 30, 18);
    rf_geomod_face_corner_append(k, *v520, 1.8974741, 4.3647552, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v521 = (int *)sub_552200((_DWORD *)v818 + 30, 18);
    rf_geomod_face_corner_append(k, *v521, 1.8974741, 0.364755, 0.0, 0.0);
    v522 = (int *)sub_552200((_DWORD *)v818 + 30, 24);
    rf_geomod_face_corner_append(k, *v522, 0.36800101, 2.911588, 0.0, 0.0);
    v523 = (int *)sub_552200((_DWORD *)v818 + 30, 21);
    rf_geomod_face_corner_append(k, *v523, 1.738066, 2.1138599, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v524 = (int *)sub_552200((_DWORD *)v818 + 30, 13);
    rf_geomod_face_corner_append(k, *v524, 4.0486469, 0.86779398, 0.0, 0.0);
    v525 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v525, 0.263616, 2.1298981, 0.0, 0.0);
    v526 = (int *)sub_552200((_DWORD *)v818 + 30, 19);
    rf_geomod_face_corner_append(k, *v526, 3.127939, 1.834304, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v527 = (int *)sub_552200((_DWORD *)v818 + 30, 26);
    rf_geomod_face_corner_append(k, *v527, 0.322384, 0.844796, 0.0, 0.0);
    v528 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v528, 3.7363839, 1.718423, 0.0, 0.0);
    v529 = (int *)sub_552200((_DWORD *)v818 + 30, 25);
    rf_geomod_face_corner_append(k, *v529, 5.2310772, 0.84479398, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v530 = (int *)sub_552200((_DWORD *)v818 + 30, 6);
    rf_geomod_face_corner_append(k, *v530, 0.244564, 0.19046, 0.0, 0.0);
    v531 = (int *)sub_552200((_DWORD *)v818 + 30, 13);
    rf_geomod_face_corner_append(k, *v531, 1.048647, 3.867794, 0.0, 0.0);
    v532 = (int *)sub_552200((_DWORD *)v818 + 30, 17);
    rf_geomod_face_corner_append(k, *v532, 0.81517702, 0.83330798, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v533 = (int *)sub_552200((_DWORD *)v818 + 30, 29);
    rf_geomod_face_corner_append(k, *v533, 1.637579, 1.432768, 0.0, 0.0);
    v534 = (int *)sub_552200((_DWORD *)v818 + 30, 11);
    rf_geomod_face_corner_append(k, *v534, 1.429511, 0.67838597, 0.0, 0.0);
    v535 = (int *)sub_552200((_DWORD *)v818 + 30, 17);
    rf_geomod_face_corner_append(k, *v535, 0.81517702, 1.833308, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v536 = (int *)sub_552200((_DWORD *)v818 + 30, 6);
    rf_geomod_face_corner_append(k, *v536, 3.2445641, 0.19046, 0.0, 0.0);
    v537 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v537, 0.263616, 5.1298981, 0.0, 0.0);
    v538 = (int *)sub_552200((_DWORD *)v818 + 30, 13);
    rf_geomod_face_corner_append(k, *v538, 4.0486469, 3.867794, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v539 = (int *)sub_552200((_DWORD *)v818 + 30, 32);
    rf_geomod_face_corner_append(k, *v539, 0.49537301, 0.48744699, 0.0, 0.0);
    v540 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v540, 1.263616, 5.1298981, 0.0, 0.0);
    v541 = (int *)sub_552200((_DWORD *)v818 + 30, 6);
    rf_geomod_face_corner_append(k, *v541, 4.2445641, 0.19046, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v542 = (int *)sub_552200((_DWORD *)v818 + 30, 29);
    rf_geomod_face_corner_append(k, *v542, 0.155204, 1.432768, 0.0, 0.0);
    v543 = (int *)sub_552200((_DWORD *)v818 + 30, 15);
    rf_geomod_face_corner_append(k, *v543, 1.7184221, 1.274464, 0.0, 0.0);
    v544 = (int *)sub_552200((_DWORD *)v818 + 30, 11);
    rf_geomod_face_corner_append(k, *v544, 0.155204, 0.67838597, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v545 = (int *)sub_552200((_DWORD *)v818 + 30, 5);
    rf_geomod_face_corner_append(k, *v545, 1.818027, 0.370774, 0.0, 0.0);
    v546 = (int *)sub_552200((_DWORD *)v818 + 30, 19);
    rf_geomod_face_corner_append(k, *v546, 0.127939, 0.83430398, 0.0, 0.0);
    v547 = (int *)sub_552200((_DWORD *)v818 + 30, 4);
    rf_geomod_face_corner_append(k, *v547, 1.558669, 1.326786, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v548 = (int *)sub_552200((_DWORD *)v818 + 30, 22);
    rf_geomod_face_corner_append(k, *v548, 0.152913, 3.7791049, 0.0, 0.0);
    v549 = (int *)sub_552200((_DWORD *)v818 + 30, 32);
    rf_geomod_face_corner_append(k, *v549, 1.495373, 1.487447, 0.0, 0.0);
    v550 = (int *)sub_552200((_DWORD *)v818 + 30, 31);
    rf_geomod_face_corner_append(k, *v550, 1.0096821, 0.354846, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v551 = (int *)sub_552200((_DWORD *)v818 + 30, 23);
    rf_geomod_face_corner_append(k, *v551, 0.91923499, 3.231869, 0.0, 0.0);
    v552 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v552, 2.2636161, 5.1298981, 0.0, 0.0);
    v553 = (int *)sub_552200((_DWORD *)v818 + 30, 32);
    rf_geomod_face_corner_append(k, *v553, 1.495373, 0.48744699, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v554 = (int *)sub_552200((_DWORD *)v818 + 30, 10);
    rf_geomod_face_corner_append(k, *v554, 1.035591, 1.403108, 0.0, 0.0);
    v555 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v555, 2.2636161, 2.1298981, 0.0, 0.0);
    v556 = (int *)sub_552200((_DWORD *)v818 + 30, 23);
    rf_geomod_face_corner_append(k, *v556, 0.91923499, 0.231869, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v557 = (int *)sub_552200((_DWORD *)v818 + 30, 3);
    rf_geomod_face_corner_append(k, *v557, 0.38341501, 0.28157699, 0.0, 0.0);
    v558 = (int *)sub_552200((_DWORD *)v818 + 30, 0);
    rf_geomod_face_corner_append(k, *v558, 1.5239739, 0.863684, 0.0, 0.0);
    v559 = (int *)sub_552200((_DWORD *)v818 + 30, 2);
    rf_geomod_face_corner_append(k, *v559, 1.809996, 0.281578, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v560 = (int *)sub_552200((_DWORD *)v818 + 30, 10);
    rf_geomod_face_corner_append(k, *v560, 1.035591, 1.403108, 0.0, 0.0);
    v561 = (int *)sub_552200((_DWORD *)v818 + 30, 23);
    rf_geomod_face_corner_append(k, *v561, 0.91923499, 0.231869, 0.0, 0.0);
    v562 = (int *)sub_552200((_DWORD *)v818 + 30, 8);
    rf_geomod_face_corner_append(k, *v562, 0.210217, 1.492626, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v563 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v563, 0.94427103, 1.844795, 0.0, 0.0);
    v564 = (int *)sub_552200((_DWORD *)v818 + 30, 2);
    rf_geomod_face_corner_append(k, *v564, 0.80999601, 0.281578, 0.0, 0.0);
    v565 = (int *)sub_552200((_DWORD *)v818 + 30, 0);
    rf_geomod_face_corner_append(k, *v565, 0.523974, 0.863684, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v566 = (int *)sub_552200((_DWORD *)v818 + 30, 18);
    rf_geomod_face_corner_append(k, *v566, 0.28157499, 4.3647552, 0.0, 0.0);
    v567 = (int *)sub_552200((_DWORD *)v818 + 30, 22);
    rf_geomod_face_corner_append(k, *v567, 1.844793, 3.7791049, 0.0, 0.0);
    v568 = (int *)sub_552200((_DWORD *)v818 + 30, 12);
    rf_geomod_face_corner_append(k, *v568, 0.28157601, 0.70401597, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v569 = (int *)sub_552200((_DWORD *)v818 + 30, 7);
    rf_geomod_face_corner_append(k, *v569, 1.844793, 1.553894, 0.0, 0.0);
    v570 = (int *)sub_552200((_DWORD *)v818 + 30, 22);
    rf_geomod_face_corner_append(k, *v570, 1.844793, 0.77910501, 0.0, 0.0);
    v571 = (int *)sub_552200((_DWORD *)v818 + 30, 18);
    rf_geomod_face_corner_append(k, *v571, 0.28157499, 1.364755, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v572 = (int *)sub_552200((_DWORD *)v818 + 30, 15);
    rf_geomod_face_corner_append(k, *v572, 1.591735, 0.281578, 0.0, 0.0);
    v573 = (int *)sub_552200((_DWORD *)v818 + 30, 2);
    rf_geomod_face_corner_append(k, *v573, 0.80999601, 0.281578, 0.0, 0.0);
    v574 = (int *)sub_552200((_DWORD *)v818 + 30, 20);
    rf_geomod_face_corner_append(k, *v574, 1.429512, 0.863684, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v575 = (int *)sub_552200((_DWORD *)v818 + 30, 26);
    rf_geomod_face_corner_append(k, *v575, 1.322384, 1.8447959, 0.0, 0.0);
    v576 = (int *)sub_552200((_DWORD *)v818 + 30, 27);
    rf_geomod_face_corner_append(k, *v576, 0.77930897, 0.281578, 0.0, 0.0);
    v577 = (int *)sub_552200((_DWORD *)v818 + 30, 4);
    rf_geomod_face_corner_append(k, *v577, 0.441331, 1.8447959, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v578 = (int *)sub_552200((_DWORD *)v818 + 30, 8);
    rf_geomod_face_corner_append(k, *v578, 0.210217, 1.492626, 0.0, 0.0);
    v579 = (int *)sub_552200((_DWORD *)v818 + 30, 23);
    rf_geomod_face_corner_append(k, *v579, 0.91923499, 0.231869, 0.0, 0.0);
    v580 = (int *)sub_552200((_DWORD *)v818 + 30, 7);
    rf_geomod_face_corner_append(k, *v580, 0.088412002, 0.55389398, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v581 = (int *)sub_552200((_DWORD *)v818 + 30, 26);
    rf_geomod_face_corner_append(k, *v581, 0.677616, 1.892063, 0.0, 0.0);
    v582 = (int *)sub_552200((_DWORD *)v818 + 30, 4);
    rf_geomod_face_corner_append(k, *v582, 1.558669, 1.326786, 0.0, 0.0);
    v583 = (int *)sub_552200((_DWORD *)v818 + 30, 19);
    rf_geomod_face_corner_append(k, *v583, 0.127939, 0.83430398, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v584 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v584, 4.9442711, 1.844795, 0.0, 0.0);
    v585 = (int *)sub_552200((_DWORD *)v818 + 30, 3);
    rf_geomod_face_corner_append(k, *v585, 3.383415, 0.28157699, 0.0, 0.0);
    v586 = (int *)sub_552200((_DWORD *)v818 + 30, 9);
    rf_geomod_face_corner_append(k, *v586, 0.54302198, 0.28157601, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v587 = (int *)sub_552200((_DWORD *)v818 + 30, 31);
    rf_geomod_face_corner_append(k, *v587, 0.0096819997, 0.354846, 0.0, 0.0);
    v588 = (int *)sub_552200((_DWORD *)v818 + 30, 6);
    rf_geomod_face_corner_append(k, *v588, 4.2445641, 1.19046, 0.0, 0.0);
    v589 = (int *)sub_552200((_DWORD *)v818 + 30, 33);
    rf_geomod_face_corner_append(k, *v589, 4.9442711, 0.18526, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v590 = (int *)sub_552200((_DWORD *)v818 + 30, 22);
    rf_geomod_face_corner_append(k, *v590, 0.152913, 0.77910501, 0.0, 0.0);
    v591 = (int *)sub_552200((_DWORD *)v818 + 30, 7);
    rf_geomod_face_corner_append(k, *v591, 0.088412002, 1.553894, 0.0, 0.0);
    v592 = (int *)sub_552200((_DWORD *)v818 + 30, 23);
    rf_geomod_face_corner_append(k, *v592, 0.91923499, 1.231869, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v593 = (int *)sub_552200((_DWORD *)v818 + 30, 8);
    rf_geomod_face_corner_append(k, *v593, 1.844793, 0.49262601, 0.0, 0.0);
    v594 = (int *)sub_552200((_DWORD *)v818 + 30, 21);
    rf_geomod_face_corner_append(k, *v594, 0.28157499, 1.11386, 0.0, 0.0);
    v595 = (int *)sub_552200((_DWORD *)v818 + 30, 16);
    rf_geomod_face_corner_append(k, *v595, 1.844793, 1.202083, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v596 = (int *)sub_552200((_DWORD *)v818 + 30, 29);
    rf_geomod_face_corner_append(k, *v596, 0.63757902, 0.43276799, 0.0, 0.0);
    v597 = (int *)sub_552200((_DWORD *)v818 + 30, 13);
    rf_geomod_face_corner_append(k, *v597, 0.048647001, 3.867794, 0.0, 0.0);
    v598 = (int *)sub_552200((_DWORD *)v818 + 30, 5);
    rf_geomod_face_corner_append(k, *v598, 0.81802702, 4.3707738, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v599 = (int *)sub_552200((_DWORD *)v818 + 30, 32);
    rf_geomod_face_corner_append(k, *v599, 0.49537301, 1.487447, 0.0, 0.0);
    v600 = (int *)sub_552200((_DWORD *)v818 + 30, 6);
    rf_geomod_face_corner_append(k, *v600, 4.2445641, 1.19046, 0.0, 0.0);
    v601 = (int *)sub_552200((_DWORD *)v818 + 30, 31);
    rf_geomod_face_corner_append(k, *v601, 0.0096819997, 0.354846, 0.0, 0.0);
    k = (float *)rf_solid_face_allocate_link(v818, v819);
    v602 = (int *)sub_552200((_DWORD *)v818 + 30, 1);
    rf_geomod_face_corner_append(k, *v602, 2.2636161, 1.129898, 0.0, 0.0);
    v603 = (int *)sub_552200((_DWORD *)v818 + 30, 10);
    rf_geomod_face_corner_append(k, *v603, 1.035591, 0.403108, 0.0, 0.0);
    v604 = (int *)sub_552200((_DWORD *)v818 + 30, 25);
    rf_geomod_face_corner_append(k, *v604, 0.76892298, 1.8076479, 0.0, 0.0);
    rf_solid_finalize_bounds((float *)v818);
    v613 = operator new(0x1CCu);
    v838 = 7;
    if ( v613 )
      v605 = (int *)rf_room460_construct_register(v613, v818, (const float *)v818 + 18, (const float *)v818 + 21);
    else
      v605 = nullptr;
    v838 = -1;
    v815 = (float *)v605;
    for ( k = (float *)rf_receiver_get_first_dword((char *)v818 + 112); k; k = (float *)rf_solid_face_next_link((int)k) )
    {
      rf_geomod_face_finalize_geometry((int)k, nullptr, 0);
      rf_geomod_room_face_attach(v815, (int)k);
    }
    rf_room_face_spatial_tree_rebuild((int *)v815);
    return v818;
  }
  else
  {
    return nullptr;
  }
}

