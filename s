[33mcommit e2ec5999e38dcde091c85968c89f9383159dc26f[m[33m ([m[1;36mHEAD -> [m[1;32mmaster[m[33m)[m
Author: MNDTGhost <9a4g0020@stust.edu.tw>
Date:   Thu Nov 22 16:10:40 2018 +0800

    init

 MNDTLibrary/.vs/MNDTLibrary/v14/.suo               | Bin [31m45568[m -> [32m57856[m bytes
 MNDTLibrary/MNDTLibrary.VC.db                      | Bin [31m17469440[m -> [32m17469440[m bytes
 MNDTLibrary/MNDTLibrary/HOG.cpp                    | 458 [32m+++++++++++++[m
 MNDTLibrary/MNDTLibrary/HOG.h                      |  92 [32m+++[m
 MNDTLibrary/MNDTLibrary/LBP.cpp                    | 313 [32m+++++++++[m
 MNDTLibrary/MNDTLibrary/LBP.h                      |  44 [32m++[m
 MNDTLibrary/MNDTLibrary/Library.cpp                | 723 [32m++++++++++++++++++++[m[31m-[m
 MNDTLibrary/MNDTLibrary/Library.h                  | 288 [32m++++++[m[31m--[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.cpp            | 184 [32m+++++[m[31m-[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.vcxproj        |   4 [32m+[m
 .../MNDTLibrary/MNDTLibrary.vcxproj.filters        |  18 [32m+[m
 MNDTLibrary/MNDTLibrary/Rect.cpp                   |  65 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/Rect.h                     |  33 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/Segment.cpp                | 219 [32m++++++[m[31m-[m
 MNDTLibrary/MNDTLibrary/Segment.h                  |  50 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/draw.cpp                   |  58 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/draw.h                     |   4 [32m+[m
 MNDTLibrary/MNDTLibrary/general.h                  |  19 [32m+[m
 ...ETFramework,Version=v4.0.AssemblyAttributes.obj | Bin [31m2988[m -> [32m2988[m bytes
 .../MNDTLibrary/x64/Debug/GaussianElimination.obj  | Bin [31m676593[m -> [32m679060[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/GraphTree.obj    | Bin [31m673786[m -> [32m676265[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/HOG.obj          | Bin [31m0[m -> [32m743722[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Image.obj        | Bin [31m681047[m -> [32m683530[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/LBP.obj          | Bin [31m0[m -> [32m802553[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Library.obj      | Bin [31m945526[m -> [32m1008137[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/MNDTLibrary.obj  | Bin [31m989914[m -> [32m1035745[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.command.1.tlog   | Bin [31m14476[m -> [32m17152[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.read.1.tlog      | Bin [31m129476[m -> [32m162934[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.write.1.tlog     | Bin [31m13232[m -> [32m26404[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m21210[m -> [32m404400[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.command.1.tlog | Bin [31m3544[m -> [32m3936[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.read.1.tlog    | Bin [31m7672[m -> [32m8324[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.write.1.tlog   | Bin [31m2280[m -> [32m2604[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Point.obj        | Bin [31m672570[m -> [32m675053[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Rect.obj         | Bin [31m700526[m -> [32m774633[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Segment.obj      | Bin [31m1595574[m -> [32m3724557[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/draw.obj         | Bin [31m674635[m -> [32m682651[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/general.obj      | Bin [31m666605[m -> [32m669084[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/vc140.pdb        | Bin [31m765952[m -> [32m1044480[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.dll              | Bin [31m413184[m -> [32m796672[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.exp              | Bin [31m4359[m -> [32m6505[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.lib              | Bin [31m7890[m -> [32m11486[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.pdb              | Bin [31m2150400[m -> [32m3829760[m bytes
 MNDTVisualization/.vs/MNDTVisualization/v14/.suo   | Bin [31m48640[m -> [32m60416[m bytes
 MNDTVisualization/MNDTVisualization.VC.db          | Bin [31m26980352[m -> [32m33202176[m bytes
 .../MNDTVisualization/Form1.Designer.cs            | 272 [32m+++++++[m[31m-[m
 MNDTVisualization/MNDTVisualization/Form1.cs       | 149 [32m++++[m[31m-[m
 .../MNDTVisualization/ImageForm.Designer.cs        |   4 [32m+[m[31m-[m
 MNDTVisualization/MNDTVisualization/MNDTLibrary.cs | 415 [32m+++++++++++[m[31m-[m
 .../MNDTVisualization/bin/Debug/MNDTLibrary.dll    | Bin [31m413184[m -> [32m796672[m bytes
 .../MNDTVisualization/bin/Debug/MNDTLibrary.pdb    | Bin [31m2150400[m -> [32m3829760[m bytes
 .../bin/Debug/MNDTVisualization.exe                | Bin [31m40448[m -> [32m50688[m bytes
 .../bin/Debug/MNDTVisualization.pdb                | Bin [31m67072[m -> [32m85504[m bytes
 ...MNDTVisualization.csproj.GenerateResource.Cache | Bin [31m1074[m -> [32m1074[m bytes
 ...ualization.csprojResolveAssemblyReference.cache | Bin [31m6291[m -> [32m6291[m bytes
 .../obj/Debug/MNDTVisualization.exe                | Bin [31m40448[m -> [32m50688[m bytes
 .../obj/Debug/MNDTVisualization.pdb                | Bin [31m67072[m -> [32m85504[m bytes
 README.md                                          |   2 [32m+[m[31m-[m
 58 files changed, 3224 insertions(+), 190 deletions(-)

[33mcommit 5875aefc17d694e7cbc638a1f9c31cbfb57b09e2[m[33m ([m[1;31morigin/master[m[33m, [m[1;31morigin/HEAD[m[33m)[m
Author: MNDTGhost <9a4g0020@stust.edu.tw>
Date:   Sun Nov 11 01:17:49 2018 +0800

    init

 MNDTLibrary/.vs/MNDTLibrary/v14/.suo               | Bin [31m50688[m -> [32m45568[m bytes
 MNDTLibrary/MNDTLibrary.VC.db                      | Bin [31m17469440[m -> [32m17469440[m bytes
 MNDTLibrary/MNDTLibrary/GaussianElimination.cpp    |  74 [32m+++[m
 MNDTLibrary/MNDTLibrary/GaussianElimination.h      |  26 [32m+[m
 MNDTLibrary/MNDTLibrary/GraphTree.cpp              |  58 [32m+++[m
 MNDTLibrary/MNDTLibrary/GraphTree.h                |  31 [32m++[m
 MNDTLibrary/MNDTLibrary/Image.cpp                  |  51 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/Image.h                    |  25 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/Library.cpp                | 578 [32m++++++++++++++++++++[m[31m-[m
 MNDTLibrary/MNDTLibrary/Library.h                  | 164 [32m++++++[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.cpp            | 143 [32m+++++[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.vcxproj        |   7 [32m+[m
 .../MNDTLibrary/MNDTLibrary.vcxproj.filters        |  33 [32m++[m
 MNDTLibrary/MNDTLibrary/Rect.cpp                   |  15 [32m+[m
 MNDTLibrary/MNDTLibrary/Rect.h                     |   6 [32m+[m
 MNDTLibrary/MNDTLibrary/Segment.cpp                | 436 [32m++++++++++++++++[m
 MNDTLibrary/MNDTLibrary/Segment.h                  | 122 [32m+++++[m
 MNDTLibrary/MNDTLibrary/draw.cpp                   |  42 [32m++[m
 MNDTLibrary/MNDTLibrary/draw.h                     |  50 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/general.h                  |  17 [32m+[m[31m-[m
 ...ETFramework,Version=v4.0.AssemblyAttributes.obj | Bin [31m2988[m -> [32m2988[m bytes
 .../MNDTLibrary/x64/Debug/GaussianElimination.obj  | Bin [31m0[m -> [32m676593[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/GraphTree.obj    | Bin [31m0[m -> [32m673786[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Image.obj        | Bin [31m672920[m -> [32m681047[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Library.obj      | Bin [31m887745[m -> [32m945526[m bytes
 .../x64/Debug/MNDTLibrary.Build.CppClean.log       |  11 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/x64/Debug/MNDTLibrary.log  |   4 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/x64/Debug/MNDTLibrary.obj  | Bin [31m953315[m -> [32m989914[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.command.1.tlog   | Bin [31m10358[m -> [32m14476[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.read.1.tlog      | Bin [31m78474[m -> [32m129476[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.write.1.tlog     | Bin [31m9102[m -> [32m13232[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m62662[m -> [32m21210[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.command.1.tlog | Bin [31m2[m -> [32m3544[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.read.1.tlog    | Bin [31m2[m -> [32m7672[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.write.1.tlog   | Bin [31m2[m -> [32m2280[m bytes
 .../x64/Debug/MNDTLibrary.tlog/unsuccessfulbuild   |   0
 MNDTLibrary/MNDTLibrary/x64/Debug/Point.obj        | Bin [31m672078[m -> [32m672570[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Rect.obj         | Bin [31m680867[m -> [32m700526[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Segment.obj      | Bin [31m0[m -> [32m1595574[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/draw.obj         | Bin [31m2692[m -> [32m674635[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/general.obj      | Bin [31m666505[m -> [32m666605[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/vc140.pdb        | Bin [31m610304[m -> [32m765952[m bytes
 .../x64/Release/GaussianElimination.obj            | Bin [31m0[m -> [32m950038[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/GraphTree.obj  | Bin [31m0[m -> [32m948794[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/Image.obj      | Bin [31m947431[m -> [32m951044[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/Library.obj    | Bin [31m1004365[m -> [32m1098412[m bytes
 .../MNDTLibrary/x64/Release/MNDTLibrary.log        |  16 [32m+[m[31m-[m
 .../MNDTLibrary/x64/Release/MNDTLibrary.obj        | Bin [31m1023543[m -> [32m1048523[m bytes
 .../x64/Release/MNDTLibrary.tlog/CL.command.1.tlog | Bin [31m3282[m -> [32m8214[m bytes
 .../x64/Release/MNDTLibrary.tlog/CL.read.1.tlog    | Bin [31m47518[m -> [32m122340[m bytes
 .../x64/Release/MNDTLibrary.tlog/CL.write.1.tlog   | Bin [31m2798[m -> [32m8234[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m15682[m -> [32m16172[m bytes
 .../Release/MNDTLibrary.tlog/link.command.1.tlog   | Bin [31m2126[m -> [32m3470[m bytes
 .../x64/Release/MNDTLibrary.tlog/link.read.1.tlog  | Bin [31m4560[m -> [32m6770[m bytes
 .../x64/Release/MNDTLibrary.tlog/link.write.1.tlog | Bin [31m1350[m -> [32m2406[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/Point.obj      | Bin [31m0[m -> [32m948095[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/Rect.obj       | Bin [31m0[m -> [32m950102[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/Segment.obj    | Bin [31m0[m -> [32m1152287[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/draw.obj       | Bin [31m0[m -> [32m950858[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/general.obj    | Bin [31m945658[m -> [32m945658[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/vc140.pdb      | Bin [31m413696[m -> [32m503808[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.dll              | Bin [31m248832[m -> [32m413184[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.exp              | Bin [31m2949[m -> [32m4359[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.lib              | Bin [31m5524[m -> [32m7890[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.pdb              | Bin [31m1536000[m -> [32m2150400[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.dll            | Bin [31m45568[m -> [32m82944[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.exp            | Bin [31m1733[m -> [32m4361[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.iobj           | Bin [31m401514[m -> [32m951452[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.ipdb           | Bin [31m135472[m -> [32m1097328[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.lib            | Bin [31m3484[m -> [32m7890[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.pdb            | Bin [31m831488[m -> [32m1060864[m bytes
 MNDTVisualization/.vs/MNDTVisualization/v14/.suo   | Bin [31m47616[m -> [32m48640[m bytes
 MNDTVisualization/MNDTVisualization.VC.db          | Bin [31m16789504[m -> [32m26980352[m bytes
 .../MNDTVisualization/Form1.Designer.cs            | 174 [32m++++++[m[31m-[m
 MNDTVisualization/MNDTVisualization/Form1.cs       |  84 [32m++[m[31m-[m
 MNDTVisualization/MNDTVisualization/MNDTLibrary.cs | 335 [32m++++++++++++[m
 .../MNDTVisualization/bin/Debug/MNDTLibrary.dll    | Bin [31m248832[m -> [32m413184[m bytes
 .../MNDTVisualization/bin/Debug/MNDTLibrary.pdb    | Bin [31m1536000[m -> [32m2150400[m bytes
 .../bin/Debug/MNDTVisualization.exe                | Bin [31m33280[m -> [32m40448[m bytes
 .../bin/Debug/MNDTVisualization.pdb                | Bin [31m54784[m -> [32m67072[m bytes
 ...MNDTVisualization.csproj.GenerateResource.Cache | Bin [31m1074[m -> [32m1074[m bytes
 ...ualization.csprojResolveAssemblyReference.cache | Bin [31m6291[m -> [32m6291[m bytes
 .../obj/Debug/MNDTVisualization.exe                | Bin [31m33280[m -> [32m40448[m bytes
 .../obj/Debug/MNDTVisualization.pdb                | Bin [31m54784[m -> [32m67072[m bytes
 README.md                                          |   2 [32m+[m[31m-[m
 85 files changed, 2399 insertions(+), 105 deletions(-)

[33mcommit d560e8df1a89d024ca69a24dd02df17658efd40f[m
Author: MNDTGhost <9a4g0020@stust.edu.tw>
Date:   Mon Oct 22 10:46:58 2018 +0800

    update

 README.md | 2 [32m+[m[31m-[m
 1 file changed, 1 insertion(+), 1 deletion(-)

[33mcommit 23b108019370d880efd0998adc4c8a799c1050e8[m
Author: MNDTGhost <9a4g0020@stust.edu.tw>
Date:   Mon Oct 22 10:26:05 2018 +0800

    init

 MNDTLibrary/.vs/MNDTLibrary/v14/.suo               | Bin [31m42496[m -> [32m50688[m bytes
 MNDTLibrary/Debug/MNDTLibrary.dll                  | Bin [31m97280[m -> [32m129024[m bytes
 MNDTLibrary/Debug/MNDTLibrary.exp                  | Bin [31m685[m -> [32m1735[m bytes
 MNDTLibrary/Debug/MNDTLibrary.ilk                  | Bin [31m559812[m -> [32m557260[m bytes
 MNDTLibrary/Debug/MNDTLibrary.lib                  | Bin [31m1752[m -> [32m3524[m bytes
 MNDTLibrary/Debug/MNDTLibrary.pdb                  | Bin [31m1265664[m -> [32m1282048[m bytes
 MNDTLibrary/MNDTLibrary.VC.db                      | Bin [31m15597568[m -> [32m17469440[m bytes
 MNDTLibrary/MNDTLibrary/Debug/Image.obj            | Bin [31m34810[m -> [32m51355[m bytes
 MNDTLibrary/MNDTLibrary/Debug/Library.obj          | Bin [31m32423[m -> [32m135783[m bytes
 MNDTLibrary/MNDTLibrary/Debug/MNDTLibrary.log      |   9 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/Debug/MNDTLibrary.obj      | Bin [31m30707[m -> [32m272639[m bytes
 .../Debug/MNDTLibrary.tlog/CL.read.1.tlog          | Bin [31m47610[m -> [32m58802[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m10720[m -> [32m12118[m bytes
 .../Debug/MNDTLibrary.tlog/link.read.1.tlog        | Bin [31m3700[m -> [32m4148[m bytes
 MNDTLibrary/MNDTLibrary/Debug/general.obj          | Bin [31m229932[m -> [32m48604[m bytes
 MNDTLibrary/MNDTLibrary/Debug/vc140.idb            | Bin [31m470016[m -> [32m543744[m bytes
 MNDTLibrary/MNDTLibrary/Debug/vc140.pdb            | Bin [31m438272[m -> [32m733184[m bytes
 MNDTLibrary/MNDTLibrary/Image.cpp                  |  15 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/Image.h                    |  13 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/Library.cpp                | 608 [32m++++++++++++++++++++[m[31m-[m
 MNDTLibrary/MNDTLibrary/Library.h                  | 193 [32m+++++++[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.cpp            | 158 [32m+++++[m[31m-[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.vcxproj        |   5 [32m+[m
 .../MNDTLibrary/MNDTLibrary.vcxproj.filters        |  15 [32m+[m
 MNDTLibrary/MNDTLibrary/Point.cpp                  |  17 [32m+[m
 MNDTLibrary/MNDTLibrary/Point.h                    |  20 [32m+[m
 MNDTLibrary/MNDTLibrary/Rect.cpp                   |  52 [32m++[m
 MNDTLibrary/MNDTLibrary/Rect.h                     |  31 [32m++[m
 MNDTLibrary/MNDTLibrary/draw.cpp                   |   0
 MNDTLibrary/MNDTLibrary/draw.h                     |  62 [32m+++[m
 MNDTLibrary/MNDTLibrary/general.cpp                |  23 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/general.h                  |  26 [32m+[m[31m-[m
 ...ETFramework,Version=v4.0.AssemblyAttributes.obj | Bin [31m2988[m -> [32m2988[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Image.obj        | Bin [31m674861[m -> [32m672920[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Library.obj      | Bin [31m712459[m -> [32m887745[m bytes
 .../x64/Debug/MNDTLibrary.Build.CppClean.log       |   2 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/x64/Debug/MNDTLibrary.log  |   4 [32m+[m[31m-[m
 MNDTLibrary/MNDTLibrary/x64/Debug/MNDTLibrary.obj  | Bin [31m675345[m -> [32m953315[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.command.1.tlog   | Bin [31m6328[m -> [32m10358[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.read.1.tlog      | Bin [31m50634[m -> [32m78474[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.write.1.tlog     | Bin [31m4602[m -> [32m9102[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m38080[m -> [32m62662[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.command.1.tlog | Bin [31m2248[m -> [32m2[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.read.1.tlog    | Bin [31m5596[m -> [32m2[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.write.1.tlog   | Bin [31m1248[m -> [32m2[m bytes
 .../x64/Debug/MNDTLibrary.tlog/unsuccessfulbuild   |   0
 MNDTLibrary/MNDTLibrary/x64/Debug/Point.obj        | Bin [31m0[m -> [32m672078[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Rect.obj         | Bin [31m0[m -> [32m680867[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/draw.obj         | Bin [31m0[m -> [32m2692[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/general.obj      | Bin [31m907836[m -> [32m666505[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/vc140.pdb        | Bin [31m528384[m -> [32m610304[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/Image.obj      | Bin [31m0[m -> [32m947431[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/Library.obj    | Bin [31m0[m -> [32m1004365[m bytes
 .../x64/Release/MNDTLibrary.Build.CppClean.log     |  18 [32m+[m
 .../MNDTLibrary/x64/Release/MNDTLibrary.log        |  12 [32m+[m
 .../MNDTLibrary/x64/Release/MNDTLibrary.obj        | Bin [31m0[m -> [32m1023543[m bytes
 .../x64/Release/MNDTLibrary.tlog/CL.command.1.tlog | Bin [31m0[m -> [32m3282[m bytes
 .../x64/Release/MNDTLibrary.tlog/CL.read.1.tlog    | Bin [31m0[m -> [32m47518[m bytes
 .../x64/Release/MNDTLibrary.tlog/CL.write.1.tlog   | Bin [31m0[m -> [32m2798[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.lastbuildstate    |   2 [32m+[m
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m0[m -> [32m15682[m bytes
 .../Release/MNDTLibrary.tlog/link.command.1.tlog   | Bin [31m0[m -> [32m2126[m bytes
 .../x64/Release/MNDTLibrary.tlog/link.read.1.tlog  | Bin [31m0[m -> [32m4560[m bytes
 .../x64/Release/MNDTLibrary.tlog/link.write.1.tlog | Bin [31m0[m -> [32m1350[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/general.obj    | Bin [31m0[m -> [32m945658[m bytes
 MNDTLibrary/MNDTLibrary/x64/Release/vc140.pdb      | Bin [31m0[m -> [32m413696[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.dll              | Bin [31m201728[m -> [32m248832[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.exp              | Bin [31m1081[m -> [32m2949[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.lib              | Bin [31m2396[m -> [32m5524[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.pdb              | Bin [31m1339392[m -> [32m1536000[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.dll            | Bin [31m0[m -> [32m45568[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.exp            | Bin [31m0[m -> [32m1733[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.iobj           | Bin [31m0[m -> [32m401514[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.ipdb           | Bin [31m0[m -> [32m135472[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.lib            | Bin [31m0[m -> [32m3484[m bytes
 MNDTLibrary/x64/Release/MNDTLibrary.pdb            | Bin [31m0[m -> [32m831488[m bytes
 MNDTVisualization/.vs/MNDTVisualization/v14/.suo   | Bin [31m47616[m -> [32m47616[m bytes
 MNDTVisualization/MNDTVisualization.VC.db          | Bin [31m8880128[m -> [32m16789504[m bytes
 .../MNDTVisualization/Form1.Designer.cs            | 216 [32m+++++++[m[31m-[m
 MNDTVisualization/MNDTVisualization/Form1.cs       | 116 [32m+++[m[31m-[m
 .../MNDTVisualization/ImageForm.Designer.cs        |  61 [32m+++[m
 MNDTVisualization/MNDTVisualization/ImageForm.cs   |  27 [32m+[m
 MNDTVisualization/MNDTVisualization/ImageForm.resx | 120 [32m++++[m
 MNDTVisualization/MNDTVisualization/MNDTLibrary.cs | 389 [32m++++++++++++[m[31m-[m
 .../MNDTVisualization/MNDTVisualization.csproj     |  11 [32m+[m[31m-[m
 MNDTVisualization/MNDTVisualization/Program.cs     |   2 [32m+[m[31m-[m
 .../MNDTVisualization/bin/Debug/MNDTLibrary.dll    | Bin [31m201728[m -> [32m248832[m bytes
 .../MNDTVisualization/bin/Debug/MNDTLibrary.pdb    | Bin [31m1339392[m -> [32m1536000[m bytes
 .../bin/Debug/MNDTVisualization.exe                | Bin [31m23040[m -> [32m33280[m bytes
 .../bin/Debug/MNDTVisualization.pdb                | Bin [31m36352[m -> [32m54784[m bytes
 ...urces => MNDTVisualization.ImageForm.resources} | Bin
 .../obj/Debug/MNDTVisualization.MNDT.resources     | Bin [31m0[m -> [32m180[m bytes
 .../MNDTVisualization.csproj.FileListAbsolute.txt  |   3 [32m+[m[31m-[m
 ...MNDTVisualization.csproj.GenerateResource.Cache | Bin [31m1012[m -> [32m1074[m bytes
 ...ualization.csprojResolveAssemblyReference.cache | Bin [31m6291[m -> [32m6291[m bytes
 .../obj/Debug/MNDTVisualization.exe                | Bin [31m23040[m -> [32m33280[m bytes
 .../obj/Debug/MNDTVisualization.pdb                | Bin [31m36352[m -> [32m54784[m bytes
 .../DesignTimeResolveAssemblyReferencesInput.cache | Bin [31m0[m -> [32m7383[m bytes
 ...tedFile_036C0B5B-1481-4323-8D20-8F5ADCB23D92.cs |   0
 ...tedFile_5937a670-0e60-4077-877b-f7221da3dda1.cs |   0
 ...tedFile_E7A71F73-0F8D-4B9B-B56E-8E70B10BC5D3.cs |   0
 README.md                                          |   2 [32m+[m[31m-[m
 102 files changed, 2174 insertions(+), 58 deletions(-)

[33mcommit 3350fc46aca74b53e8eee6eff66440b4af488690[m
Author: MNDTGhost <9a4g0020@stust.edu.tw>
Date:   Wed Oct 3 23:15:50 2018 +0800

    init

 MNDTLibrary/.vs/MNDTLibrary/v14/.suo               | Bin [31m0[m -> [32m42496[m bytes
 MNDTLibrary/Debug/MNDTLibrary.dll                  | Bin [31m0[m -> [32m97280[m bytes
 MNDTLibrary/Debug/MNDTLibrary.exp                  | Bin [31m0[m -> [32m685[m bytes
 MNDTLibrary/Debug/MNDTLibrary.ilk                  | Bin [31m0[m -> [32m559812[m bytes
 MNDTLibrary/Debug/MNDTLibrary.lib                  | Bin [31m0[m -> [32m1752[m bytes
 MNDTLibrary/Debug/MNDTLibrary.pdb                  | Bin [31m0[m -> [32m1265664[m bytes
 MNDTLibrary/MNDTLibrary.VC.VC.opendb               | Bin [31m0[m -> [32m42[m bytes
 MNDTLibrary/MNDTLibrary.VC.db                      | Bin [31m0[m -> [32m15597568[m bytes
 MNDTLibrary/MNDTLibrary.sln                        |  28 [32m+[m
 MNDTLibrary/MNDTLibrary/Debug/Image.obj            | Bin [31m0[m -> [32m34810[m bytes
 MNDTLibrary/MNDTLibrary/Debug/Library.obj          | Bin [31m0[m -> [32m32423[m bytes
 MNDTLibrary/MNDTLibrary/Debug/MNDTLibrary.log      |   3 [32m+[m
 MNDTLibrary/MNDTLibrary/Debug/MNDTLibrary.obj      | Bin [31m0[m -> [32m30707[m bytes
 .../Debug/MNDTLibrary.tlog/CL.command.1.tlog       | Bin [31m0[m -> [32m3330[m bytes
 .../Debug/MNDTLibrary.tlog/CL.read.1.tlog          | Bin [31m0[m -> [32m47610[m bytes
 .../Debug/MNDTLibrary.tlog/CL.write.1.tlog         | Bin [31m0[m -> [32m6228[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.lastbuildstate    |   2 [32m+[m
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m0[m -> [32m10720[m bytes
 .../Debug/MNDTLibrary.tlog/link.command.1.tlog     | Bin [31m0[m -> [32m3250[m bytes
 .../Debug/MNDTLibrary.tlog/link.read.1.tlog        | Bin [31m0[m -> [32m3700[m bytes
 .../Debug/MNDTLibrary.tlog/link.write.1.tlog       | Bin [31m0[m -> [32m1102[m bytes
 MNDTLibrary/MNDTLibrary/Debug/general.obj          | Bin [31m0[m -> [32m229932[m bytes
 MNDTLibrary/MNDTLibrary/Debug/vc140.idb            | Bin [31m0[m -> [32m470016[m bytes
 MNDTLibrary/MNDTLibrary/Debug/vc140.pdb            | Bin [31m0[m -> [32m438272[m bytes
 MNDTLibrary/MNDTLibrary/Image.cpp                  |  28 [32m+[m
 MNDTLibrary/MNDTLibrary/Image.h                    |  26 [32m+[m
 MNDTLibrary/MNDTLibrary/Library.cpp                | 437 [32m+++++++++++++[m
 MNDTLibrary/MNDTLibrary/Library.h                  |  87 [32m+++[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.cpp            |  36 [32m++[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.vcxproj        | 163 [32m+++++[m
 .../MNDTLibrary/MNDTLibrary.vcxproj.filters        |  42 [32m++[m
 MNDTLibrary/MNDTLibrary/MNDTLibrary.vcxproj.user   |   7 [32m+[m
 MNDTLibrary/MNDTLibrary/general.cpp                |  13 [32m+[m
 MNDTLibrary/MNDTLibrary/general.h                  |  36 [32m++[m
 ...ETFramework,Version=v4.0.AssemblyAttributes.asm |   4 [32m+[m
 ...ETFramework,Version=v4.0.AssemblyAttributes.obj | Bin [31m0[m -> [32m2988[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Image.obj        | Bin [31m0[m -> [32m674861[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/Library.obj      | Bin [31m0[m -> [32m712459[m bytes
 .../x64/Debug/MNDTLibrary.Build.CppClean.log       |  22 [32m+[m
 MNDTLibrary/MNDTLibrary/x64/Debug/MNDTLibrary.log  |   4 [32m+[m
 MNDTLibrary/MNDTLibrary/x64/Debug/MNDTLibrary.obj  | Bin [31m0[m -> [32m675345[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.command.1.tlog   | Bin [31m0[m -> [32m6328[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.read.1.tlog      | Bin [31m0[m -> [32m50634[m bytes
 .../x64/Debug/MNDTLibrary.tlog/CL.write.1.tlog     | Bin [31m0[m -> [32m4602[m bytes
 .../MNDTLibrary.tlog/MNDTLibrary.lastbuildstate    |   2 [32m+[m
 .../MNDTLibrary.tlog/MNDTLibrary.write.1u.tlog     | Bin [31m0[m -> [32m38080[m bytes
 .../x64/Debug/MNDTLibrary.tlog/TZRES.DLL.bi        |   0
 .../x64/Debug/MNDTLibrary.tlog/link.command.1.tlog | Bin [31m0[m -> [32m2248[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.read.1.tlog    | Bin [31m0[m -> [32m5596[m bytes
 .../x64/Debug/MNDTLibrary.tlog/link.write.1.tlog   | Bin [31m0[m -> [32m1248[m bytes
 .../x64/Debug/MNDTLibrary.tlog/metagen.read.1.tlog |   1 [32m+[m
 .../Debug/MNDTLibrary.tlog/metagen.write.1.tlog    |   1 [32m+[m
 ...DTLibrary.vcxprojResolveAssemblyReference.cache | Bin [31m0[m -> [32m711[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/general.obj      | Bin [31m0[m -> [32m907836[m bytes
 MNDTLibrary/MNDTLibrary/x64/Debug/vc140.pdb        | Bin [31m0[m -> [32m528384[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.dll              | Bin [31m0[m -> [32m201728[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.dll.metagen      |   7 [32m+[m
 MNDTLibrary/x64/Debug/MNDTLibrary.exp              | Bin [31m0[m -> [32m1081[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.lib              | Bin [31m0[m -> [32m2396[m bytes
 MNDTLibrary/x64/Debug/MNDTLibrary.pdb              | Bin [31m0[m -> [32m1339392[m bytes
 MNDTVisualization/.vs/MNDTVisualization/v14/.suo   | Bin [31m0[m -> [32m47616[m bytes
 MNDTVisualization/MNDTVisualization.VC.VC.opendb   | Bin [31m0[m -> [32m42[m bytes
 MNDTVisualization/MNDTVisualization.VC.db          | Bin [31m0[m -> [32m8880128[m bytes
 MNDTVisualization/MNDTVisualization.sln            |  22 [32m+[m
 MNDTVisualization/MNDTVisualization/App.config     |   6 [32m+[m
 .../MNDTVisualization/Form1.Designer.cs            | 705 [32m+++++++++++++++++++++[m
 MNDTVisualization/MNDTVisualization/Form1.cs       | 163 [32m+++++[m
 MNDTVisualization/MNDTVisualization/Form1.resx     | 120 [32m++++[m
 MNDTVisualization/MNDTVisualization/MNDTLibrary.cs | 139 [32m++++[m
 .../MNDTVisualization/MNDTVisualization.csproj     |  96 [32m+++[m
 MNDTVisualization/MNDTVisualization/Program.cs     |  22 [32m+[m
 .../MNDTVisualization/Properties/AssemblyInfo.cs   |  36 [32m++[m
 .../Properties/Resources.Designer.cs               |  71 [32m+++[m
 .../MNDTVisualization/Properties/Resources.resx    | 117 [32m++++[m
 .../Properties/Settings.Designer.cs                |  30 [32m+[m
 .../MNDTVisualization/Properties/Settings.settings |   7 [32m+[m
 .../MNDTVisualization/bin/Debug/MNDTLibrary.dll    | Bin [31m0[m -> [32m201728[m bytes
 .../MNDTVisualization/bin/Debug/MNDTLibrary.pdb    | Bin [31m0[m -> [32m1339392[m bytes
 .../bin/Debug/MNDTVisualization.exe                | Bin [31m0[m -> [32m23040[m bytes
 .../bin/Debug/MNDTVisualization.exe.config         |   6 [32m+[m
 .../bin/Debug/MNDTVisualization.pdb                | Bin [31m0[m -> [32m36352[m bytes
 .../bin/Debug/MNDTVisualization.vshost.exe         | Bin [31m0[m -> [32m22688[m bytes
 .../bin/Debug/MNDTVisualization.vshost.exe.config  |   6 [32m+[m
 .../Debug/MNDTVisualization.vshost.exe.manifest    |  11 [32m+[m
 .../DesignTimeResolveAssemblyReferences.cache      | Bin [31m0[m -> [32m1464[m bytes
 .../DesignTimeResolveAssemblyReferencesInput.cache | Bin [31m0[m -> [32m7379[m bytes
 .../obj/Debug/MNDTVisualization.Form1.resources    | Bin [31m0[m -> [32m180[m bytes
 ...NDTVisualization.Properties.Resources.resources | Bin [31m0[m -> [32m180[m bytes
 .../MNDTVisualization.csproj.FileListAbsolute.txt  |  11 [32m+[m
 ...MNDTVisualization.csproj.GenerateResource.Cache | Bin [31m0[m -> [32m1012[m bytes
 ...ualization.csprojResolveAssemblyReference.cache | Bin [31m0[m -> [32m6291[m bytes
 .../obj/Debug/MNDTVisualization.exe                | Bin [31m0[m -> [32m23040[m bytes
 .../obj/Debug/MNDTVisualization.pdb                | Bin [31m0[m -> [32m36352[m bytes
 ...tedFile_036C0B5B-1481-4323-8D20-8F5ADCB23D92.cs |   0
 ...tedFile_5937a670-0e60-4077-877b-f7221da3dda1.cs |   0
 ...tedFile_E7A71F73-0F8D-4B9B-B56E-8E70B10BC5D3.cs |   0
 README.md                                          |   1 [32m+[m
 97 files changed, 2518 insertions(+)
