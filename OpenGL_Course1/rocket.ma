//Maya ASCII 2012 scene
//Name: rocket.ma
//Last modified: Wed, Oct 05, 2011 08:15:17 PM
//Codeset: 950
requires maya "2012";
requires "stereoCamera" "10.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2012";
fileInfo "version" "2012";
fileInfo "cutIdentifier" "001200000000-796618";
fileInfo "osv" "Microsoft Windows 7 Ultimate Edition, 64-bit Windows 7  (Build 7600)\n";
createNode transform -s -n "persp";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 16.760171238432587 -3.2889480634231774 11.219956713639482 ;
	setAttr ".r" -type "double3" -710.73835272941244 56.200000000003435 1.4293455641401056e-015 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 20.435458105010305;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 100.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 100.1 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 100.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "pCylinder1";
	setAttr ".r" -type "double3" 90 0 0 ;
createNode mesh -n "pCylinderShape1" -p "pCylinder1";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".dr" 1;
createNode lightLinker -s -n "lightLinker1";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode displayLayerManager -n "layerManager";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
createNode polyCylinder -n "polyCylinder1";
	setAttr ".sa" 12;
	setAttr ".sc" 1;
	setAttr ".cuv" 3;
createNode polySplitRing -n "polySplitRing1";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "e[24:35]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 2.2204460492503131e-016 1 0 0 -1 2.2204460492503131e-016 0
		 0 0 0 1;
	setAttr ".wt" 0.30727443099021912;
	setAttr ".re" 29;
	setAttr ".sma" 29.999999999999996;
	setAttr ".p[0]"  0 0 1;
	setAttr ".fq" yes;
createNode polyTweak -n "polyTweak1";
	setAttr ".uopa" yes;
	setAttr -s 26 ".tk[0:25]" -type "float3"  0 -2.29195833 0 0 -2.29195833
		 0 0 -2.29195833 0 0 -2.29195833 0 0 -2.29195833 0 0 -2.29195833 -5.0891698e-016 0
		 -2.29195833 -2.220446e-016 0 -2.29195833 0 0 -2.29195833 0 0 -2.29195833 0 0 -2.29195833
		 -2.220446e-016 0 -2.29195833 -5.0891698e-016 0 6.58994389 7.7715612e-016 0 6.58994389
		 2.220446e-016 0 6.58994389 2.220446e-016 0 6.58994389 2.220446e-016 0 6.58994389
		 7.7715612e-016 0 6.58994389 1.4632615e-015 0 6.58994389 2.220446e-016 0 6.58994389
		 2.220446e-016 0 6.58994389 0 0 6.58994389 2.220446e-016 0 6.58994389 2.220446e-016
		 0 6.58994389 1.4632615e-015 0 -2.29195833 -5.0891698e-016 0 6.58994389 1.4632615e-015;
createNode polySplitRing -n "polySplitRing2";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 11 "e[60:61]" "e[63]" "e[65]" "e[67]" "e[69]" "e[71]" "e[73]" "e[75]" "e[77]" "e[79]" "e[81]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 2.2204460492503131e-016 1 0 0 -1 2.2204460492503131e-016 0
		 0 0 0 1;
	setAttr ".wt" 0.32629743218421936;
	setAttr ".re" 60;
	setAttr ".sma" 29.999999999999996;
	setAttr ".p[0]"  0 0 1;
	setAttr ".fq" yes;
createNode polyExtrudeFace -n "polyExtrudeFace1";
	setAttr ".ics" -type "componentList" 3 "f[3]" "f[7]" "f[11]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 2.2204460492503131e-016 1 0 0 -1 2.2204460492503131e-016 0
		 0 0 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 0.066987336 -0.066987336 -1.6200931 ;
	setAttr ".rs" 65112;
	setAttr ".lt" -type "double3" 6.4184768611141862e-017 2.6714741530042829e-016 0.1180779259038276 ;
	setAttr ".ls" -type "double3" 1 1 1.5390902458201785 ;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.86602532863616943 -1 -3.2919583320617676 ;
	setAttr ".cbx" -type "double3" 1 0.86602532863616943 0.051772117614746316 ;
createNode polyTweak -n "polyTweak2";
	setAttr ".uopa" yes;
	setAttr -s 26 ".tk[0:25]" -type "float3"  -0.56602693 0 0.32679573 -0.32679573
		 0 0.56602693 0 0 0.65359145 0.32679573 0 0.56602693 0.56602693 0 0.32679573 0.65359145
		 0 3.2653448e-016 0.56602693 0 -0.32679573 0.32679573 0 -0.56602693 0 0 -0.65359145
		 -0.32679573 0 -0.56602693 -0.56602693 0 -0.32679573 -0.65359145 0 3.2653448e-016
		 -0.8661862 8.8817842e-016 0.5000928 -0.5000928 8.8817842e-016 0.8661862 0 8.8817842e-016
		 1.00018560886 0.5000928 8.8817842e-016 0.8661862 0.8661862 8.8817842e-016 0.5000928
		 1.00018560886 8.8817842e-016 -1.4573773e-015 0.8661862 8.8817842e-016 -0.5000928
		 0.5000928 8.8817842e-016 -0.8661862 0 8.8817842e-016 -1.00018560886 -0.5000928 8.8817842e-016
		 -0.8661862 -0.8661862 8.8817842e-016 -0.5000928 -1.00018560886 8.8817842e-016 -1.4573773e-015
		 0 0 3.2653448e-016 0 8.8817842e-016 -1.4573773e-015;
createNode polySmoothFace -n "polySmoothFace1";
	setAttr ".ics" -type "componentList" 4 "f[0:2]" "f[4:6]" "f[8:10]" "f[12:71]";
	setAttr ".dv" 3;
	setAttr ".suv" yes;
	setAttr ".ps" 0.10000000149011612;
	setAttr ".ro" 1;
	setAttr ".ma" yes;
	setAttr ".m08" yes;
createNode polyTweak -n "polyTweak3";
	setAttr ".uopa" yes;
	setAttr -s 23 ".tk";
	setAttr ".tk[27:28]" -type "float3" 0.0052075004 -0.40541726 -0.36216018  
		-0.36216003 -0.40541726 0.0052073444 ;
	setAttr ".tk[31:32]" -type "float3" 0.26590714 -0.3949295 0.15268445  0.13492066 
		-0.3949295 -0.33616719 ;
	setAttr ".tk[35:36]" -type "float3" -0.33456078 -0.39304247 0.13427581  
		0.15195483 -0.39304247 0.26463735 ;
	setAttr ".tk[50:61]" -type "float3" -0.87190431 -1.7135429 -1.2486103  -1.2486103 
		-1.7135429 -0.87190431  0.088555805 -0.38054785 -0.27918419  -0.27918404 -0.38054788 
		0.088555671  -0.71737051 -1.7135429 1.1107279  -0.20277393 -1.7135429 1.2486103  
		-0.30585101 -0.39292285 0.033257812  0.17692395 -0.39292282 0.16261704  1.2486103 
		-1.7135429 -0.20277403  1.1107279 -1.7135429 -0.71737057  0.16214563 -0.39103585 
		0.17853007  0.031988066 -0.39103588 -0.30722865 ;
createNode polySmoothFace -n "polySmoothFace2";
	setAttr ".ics" -type "componentList" 1 "f[0:4034]";
	setAttr ".suv" yes;
	setAttr ".ps" 0.10000000149011612;
	setAttr ".ro" 1;
	setAttr ".ma" yes;
	setAttr ".m08" yes;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultShaderList1;
	setAttr -s 2 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :renderGlobalsList1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "polySmoothFace2.out" "pCylinderShape1.i";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "polyTweak1.out" "polySplitRing1.ip";
connectAttr "pCylinderShape1.wm" "polySplitRing1.mp";
connectAttr "polyCylinder1.out" "polyTweak1.ip";
connectAttr "polySplitRing1.out" "polySplitRing2.ip";
connectAttr "pCylinderShape1.wm" "polySplitRing2.mp";
connectAttr "polyTweak2.out" "polyExtrudeFace1.ip";
connectAttr "pCylinderShape1.wm" "polyExtrudeFace1.mp";
connectAttr "polySplitRing2.out" "polyTweak2.ip";
connectAttr "polyTweak3.out" "polySmoothFace1.ip";
connectAttr "polyExtrudeFace1.out" "polyTweak3.ip";
connectAttr "polySmoothFace1.out" "polySmoothFace2.ip";
connectAttr "pCylinderShape1.iog" ":initialShadingGroup.dsm" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
// End of rocket.ma
