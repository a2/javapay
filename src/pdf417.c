#include "pdf417.h"

static const char *const s_codewords = "LYnWw;F5)Q]NcPxLYqWw>Q]Q--JLYtWw[F5:Q]TcP3LYwWw_Q]W--PF5=Ww|F5@LYzcP9LY2F5^Q]c--V--YWxCF5{F5~Q]i--b--eWxIcP^F6LQ]o--oLY<Q]vF6OQ]yWxVcP~F6RcP{--uLY]LY?F6UQ]4Q]1cQE--xWxb--0F6XLY`F6a--3Q]7cQK--:Wxh--6F6wLZAWx3LZWQ]%cQd--@LZG--=F62Q],Wx9LZcLZMcQj--{LZT--^F68Q]_Wx(-BUWx6--~F6`F6zWx/-BaLZZQ^bF7AQ]\"WyB-B5F65Q^hWy.LZfWyHLa/Q^FQ^nQ_vF6#Q^tWzVLZlLZ\"F8OF6*Q^$La?LZrLaFQ_1F6;Q^+F8UF6]LaLLa`LZ4LaR-C0Q^eF7!F8a-BXLakLbAF6}F7)-C6LZ!LaqF8g-BdF7:-C$F7D-ClF8tLZ)F8LLbT-BjLa<Q__F7J-Cr-C=-BpF8RF8zF7PLa]LbZ-B2-Cx-C^F7cF8XF85LaC-C3Lbf-B8F8d-C~F7i-C9F8#-B&cSa-DRF7o-C:F8]-B.F8wLb4-CAcSg-DXF7%-C@F8}-CGF82-Dd-CMcSmF9DQ_s-C{-D2WzS-DBF9ccR^Wz~-D8Q_ycS#-D&WzY-DUF!qcR~W0ELdQQ_4-DaQ{[WzeW0KF!wQ_!Q`9LdWWzkW0jQ{|Q_)Q`(-E@Q_:Q`/F!2LbQLchLdcQ_[Q{H-E{Wz3LcnF!8LbWLct-FBQ_|F!F-FHWz9Lc+-FOLbcF!LF!?Q`CF!RLd1Lbi-E,-FUQ`IF!tF!`LboLdTLd7Lbu-E=-FaF8?F!zF#ALb1-E^-FgQ`bF!5-FmF8`-E~-FzLb7-FEF#ZQ`hcU8-F5F9A-FRF#fLb%F!]-F#F9GcU&-F}Lb,-FXF$<F9M-FdLfyF9SW2gQ~Y-Dz-F2-HRF9ZW2mF$]Lb\"Q}ELf4-D5Q}K-HXF9fLe(F$}LcFLe/Lf!-D#F$n-HdF9lF$tF%D-D*-HO-HjF9rF$?F%J-D;-HU-Hw-D}F$`F%WF9!-HaLf|-ED-Hg-H2F9)cXDF%c-EJ-Hz-H8-EP-H5F%i-EiW4&-H&-EoQ\"m-H.Q{>LhKF%7W10-Jw-IGcUaF(W-JtQ{_-J2F(TW16-J8Lh_Q{\"-J`-JzW1$-L]F(ZQ|F-L}Lh\"Q|L-`s-J5LdyG0SF(fQ|YMS^-J#W1~-`yF(lLd4G0Y-J*Q|eMS~-J]Ld!-`4-J}Q|kG0e-KDLd)-`!-L?Ld:G0kLkbF#W-`)F*7Ld|dKhF*%Q|9-`[-MMF#cG03MS@LeCdKnR<2F#i-`|XrcLeIG09G0VF#odKtMS{F#u-{CR<8-F`-{IG0bF#7XsFMTBLehdK+R<&-GA-{b-`7F#%XsLG0h-GG-{h-`%F#,XsRG00-GMR=)MTa-GSXsqR=A-GfR=:-`_F$FR=@G06-GlMUoMTg-GrR>O-`\"-G)MUuG0$Q~VMU0-{FW3{G2M-{LQ~bMU=-{YW4BG2SG0~Q~hG2YMT#Q~nF,~-{eLf_Lm#G1EQ~6RFl-{kLf\"-Oe-{qQ~$F.E-{9LgFLm*G1jLgL-Ok-{(F%4F.K-|HLgeLm;Lm8F%!-OqRFiLgkF.QW#IF%)-OwLm&F%:F.WRFo-Ic-O2W#OF&C-|>F.H-IiG20Lm.F&IMVaRFu-Io-O9F.N-Iu-|_Lm>-I%G26RF0-I,-O(F.TRA3F.pLm_W6dG2$G2xRA9-O/MVXRA(-}FR>}Lib-O?F.gRBB-}LG23Lih-O`MVdLindM(R?DF(\"-}YF.mLi$G2~LnMF)FceyRF=F)LdM/-O+-K!-PH-}CF)k-}eG2(-K)ce4MVp-K:-PN-O<RC~-}kF.yRDE-PT-O]Lk9Xun-}VLk(-}9G2{F+hW$WMV8F+nXut-PER<z-Ps-}bXrZW$cG3BdJ\"R@LMV&R<5RG`-PKXrfR@RF.;dKFRHALnxR<#MW:-PQXrlLo5-}nR<*MW@-PWXrrLo#-}6R<;G4uG3gR<[G40-PpMTX-Q6-}$R<}F:gG3mXr!LpG-PvMTd-Q$F/VR=DF:m-P1Xr)LpM-~EMTj-Q+-P>R=JF:s-~KMTp-Q<-P_R=PF:yLpDMTv-Q]RH)MT1-Q}W%qG0{-\"VF:jMT8G4{LpJR=i-RERH:G1B-\"bF:pMT&G5BLpPR=o-RKRH@G1HF:;F:vMT.-RQLpVG1N-\"nF:1MT>-RWF:7G1TdPKG4^G1Z-\"6MX5-{6cg_R[fG1g-RpF:&MUG-\"$G4~-{$-RvMX#G1mXw/-RHMUMW&4-\"e-{+R]tLpuG1sRJcMX*-{<MZR-RNG1yLrA-\"k-{]G6@G5K-|E-TB-RTG1*F<&F:_-|KLroG5QG1;-TH-\"w-|QF<.-\"3-|W-TNG5d-|pF<>MYD-|v-TT-RmW#F-TZ-\"9cd+BB3G5j-ObG7d-RsW#L-TmF;Scd<BB9G5p-Oh-Ts-RyW#RBB(-\"/cd]-Ty-\"?-OnBCBBABW#X-T;G5&W#d-Vj-R;R>`F?JBAHXt7-Vp-R[dMhF?PBANRF)-Vv-R|R?A-V1-SVceQBD~F<#RF:-V.LrlW#wBEERKLXt,-V>F<*RF@-X*LrrR?MF[rRKRRF{-X;F<;R?S-X[LrxRGBBGgF<[MV5-YPLr3R?f-aMF<|XuF-aSF=CLnoB?`BB0MV#Hu7G7aR?lNNhMaALnuB@A-TjRGUHu%BB6R?rB@GG7gLn0Hu,MaGMV;B@M-TpLn6B@SF=PMV[eE:Lr@Ln$B@f-TvG3dHvFBB+MWDeE@G7sR?)B@l-T1F/MB@rF=bG3jYmu-T7MWJB@)BB~F/SYm0G7#Ln^S.S-T.MWPS.YBCEF/YNO[G7*G3vNO|-T>F/eHw1F=0G31Hw7-T_F/kBI%BCQ-~BG&n-T\"G3&MhN-USMWoBI,-UY-P;G&tF?G-~HMhTLt,G3.BI=RMt-P[G&zF?MF/3BI^Lt=G3>G&5F?S-P|BI~Lt^-~TBJEF?Y-QCB]cF?e-~ZHxCBD{-~mBJLG98G4MB]iMci-QVHxI-V*-~sBJRBEB-QbG&]G9&-~yBJX-V;-QhB]uF?x-~;BJdG9.W%neHR-V[cgNB]%BEN-Q9dZA-V|W%tBJwBETcgTB],BEg-Q(BJ2-WPW%zYo@-WV-Q/X6#-WbW%5S:0LwOR[cSBjLwUXwCNRYF[6RILMjHG$DR[iHy|BGjXwIF{T-YSRIRL0_-YYW%]RT6-YeRIX-czHu4R[uF{ZNNeRIdL0\"S,EMYA-c5Hu!R[%F{fNNkLp:L1FB@DMYG-c#Hu)R[,F{lNNqLp@-c*B@JRI2F{rHu:Lp{-c;B@PMYSBLIB@VLqBG)/B@cG5#MjvHvCMYl-c]NN(F;uBLOB@iG5*G)?HvIMYr-c}NN/F;0F{!B@oLqaG)`HvOF;6-dDB@uG5[BLaB@0F;$-dJB@%BAjBLgHvnG6J-dPB@,-SSB_!HvtBApHzkB@=G6PBLtB[L-SYB_)B[RF;~-dcMhK-SeBLzR\";BA1B_:X5x-Sk-diG&qBA.BL5MhQ-S3-doR\"[BA>B`IG&w-S9BL]MhWW(/-d%R\"|civ-e?G&2-TEF}1MhcW(?L3bG&8-TK-e`MhiW(`F}7Hw\"R^!L3hNP$Xyk-fAS/mRKtF}%G&/W)T-fGHxFRKzF},NP+R^:-fMBJORK5-fSB]lMaiBNqMh1R_IG,QNP<LsR-fZBJUMaoBNwG&`LsXG,WHxRMau-ffBJaLsdF~FB]xG8G-flBJgMa,BN8B]!F=@-frHxkLs2B|FNQKF={BN?BJtG8SB|LB])F>B-f!Mh_BC*BN`BJzG8r-f)G(Z-U0-hWHxwBC;F\"|BJ5-U6L59B]@BC[-hcBJ#-U$GACB^IBDP-hiHx/-U~GAIBJ]W+Q-hoB^O-Vm-huBJ}W+WBP<B^UR{FG/yB^tRM?-h7BKcR{LBP]L0[RM`-h%RT3Mc)BP}W=dLuz-h,L0|Mc:B~nRT9Lu5BQWW=jG!o-iFL1CF@X-j4RT(G!uGCeL1IF@d-j!RT/BFMGCkL1O-W{-j)G)+BFS-j:Mjs-XBBSTSCSW.y-kCF{1R}nBSZG)<RPW-kIRUBMfL-l\"SCYLw`GE$F{7G$:-mFL1hF]5-mLRUHS,BBU1F{%Yl&-mkG)}eEo-ohMj!S,H-onF{,Yl.C:jL1tS,NIpJG*JYl>C:pB_7S,TIpPHzhS,ZC:vNSHNN$C:1BLqS,mC:.B_%YmMC:>HznNN+Zg|NSNS,sT&7-dZNN<OJfBLwS,yIrDG*WNN]CDPMj|NN}H8@-dfHvkNb2F|FNOKCDVL1+S,;H8{HzzHvqCDb-dlNOQH9BBL8HvwCDhG*iNOWCDn-drHv2C<*B_~Hv8IrrB`FB[ICD0Hz+Hv/C<;BL?NOvCD6B`LB[OC<[Hz<Hv?CD$-d!B[UC=PBL`Hv`CD~G*7B[aBW{-d)B[gG@8F|qB[tMviB`XHwTBXBBMGB[zG@&B`qB[5MvoBMZB[]BXHB`wX5uG@.-eIdYUBXNBMfBI)G@>L3YX50BXTRV~dYaBXZW?#BI:CFxL3eX56H#XRWEBI@BXgL3kX5$CF3RWKS/jH#dL3qYoJBXmL3wSASCF9G,NS/pBXsMl>YoPCF(SE0SAYBXyF}|X5~C?MG,TSAeCF{RWjS/1C?SF~CSAkBX*L3(NQHCGBMl\"S/.BX;F~IMh[GJoG,fNQNL(OF~OS/>Rh?G,lMh|-q.F~USA9GJuB|CMiCL(UH1(NQZ-q>NUpMiIGJ0BN<Hx+L(aB|INQs-q_H1/G(1GJ6-f7Hx<-q\"BN]NQyGJ$G,4G(7-rFH1?MihBZd-f%G(%G^DF~nHx}Mx)B|UG(,-rM-f,B^qBZjBODHyQG^JB|aBKZ-rSBOJB^wGJ^B|nHyWG^PH2NBKf-rYBOWG)FBZvB|tBKl-re-gFB^8BZ1BOcBKr-rkB|zB^?CH^-gLBK!H%5BOiB^`BZ&B|<BK)CH~-gqcsA-rxL56-cwBZ.RYgF{WCIEL5$csG-r3RYm-c2BZ>L5+F{c-r9L5<csMC[uG/v-c8CIdMoV-c&BaMGAeX7@-r{G/1da2-tJMobBLLGL:GAkW=#L*wL6Kcsl-tPGAq-c`GL@G/%BLRL*2GAwW=*-tVB~kX8BGL{H4K-dA-tbBQTW=;GMBB~qS;*-thH4QYqr-tn-iCSC0Bb#BQZS;;G`lG/\"RUj-tu-iIW>JBb*GA/S;[G`rB~2RUp-t0-iOSC$GMaBQlRUv-t6-iUNSpBb[BQ4S<P-t$-inMkYCKa-itNSvBcJRa&L2HCKgL8NMke-t^Mq3NS1BcPG;|L2N-t~G<CMkk-vrCA+L2TGORBS1H0NL,]-kkNS>-vxCA]G*|GOXBS%H0T-v3IpGF|+GOdC:mG+C-v9IpMH0Z-v(C:sF|<BeGIpSG+IG|,OH^F|]-v@C:yB`<BeMIpYH0y-v{C:4BM7BeSIpeB`]-wBC:*-eqCM8IprBM%BerOIRB`}-waC:;-ew-x=IpxBM,GQzC:[-e2-x^Ip3B{WGQ5C:|BNF-x~C;Ccui-yEC;P-e]BgoIp@F}4-yXC;VcuoBguC;b-e}-ydC;0-fD-0UH8=X!XGS`NbzBNt-0aS`ZW@G-0gH8^X!dBi:Nb5-fc-05H8~W@MD)<Nb#S>MJjyH9ESE{D)]Nb*S>SD)}H9KRW*D*WC<&SFBC}4IroRW;I3eOKONU;C}!CDxMm6I3kC<.NU[C})Nb}L4pC}:OKUMm$D,TCD3L4vC~CH9dH2vD,ZNcDG.eC~ICD9H21CRkC<_F\"NH;KIr6G.kNp;CD(F\"TCRqH9pB}TH;QC=FBPCCRwC=MB}ZH;WIr=-g<CR2CD{BPICR8C=S-g]C\"\"Ir^cw)I5$CEB-hZCR/H9&-hfDAFCEHX$5CR?C=eW]oDALC=xS@uCR`CEgSHdD/1C=3RZMDAkCEmNXSCSTMvfMpBBlQSOFL6;HD[X,+H4[M93MvlG:$BlWSOLGBvHD|MvrB\"1M99SORBRkBlcMvx-jTHECMv3-j7BliH#UT%qHEINd`ZgQBloG[DT%wBluH#aZgWCT+NeAT%2H=sG[JT%8Bl1Mv:OIOCT<NeGT%?H=yG[POIUBl7H#mT%`HEhG[VOIaBl%H#sOIgCT}G[bIp=Bl,C?JOIzDChIt:Ip^CUQCF^OI5DCnC?PIp~Bl\"NefIqECUWBX&C;xBmFCF~IqXGX9H##C;3L[jIt{IqdRwJBX.C;9GX(G[uC;(L[pC?bC;{GX/BX>C<BL[vCGKYz|GX?C?heS9GX`CGQCDSBnyC?uY0CHGYIuUCDYM#~CGdY0I-5hC?0T(<Bn4BYMZiyHGeCGjS`7-5nC?6T(]GYNBYSS`%HGkCGpT(}-5tC?^S`,Bn)CG&OKw-5zBYxT)WBn:Rh<Ncf-55XAyOK2CWNRh]NclH?>XA4OK8Bn|Rh}NcrCWTRiDIsU-5+Mx%OK`BoCSQnH!DCWZL(wIsa-5<RiWH!JBoISQtIsg-5]L(2H!PDE(RicC=^CWyL(8Is5BohMx^CE&-6QL(&C=~GaEH%2CE.L^*NgcC>EGaKG^lCE>L^;H%8C>dGaQNgiCFMGaWGKUdmpBp_G^rBW~HI6MyRG@#-7(GKadmvBp\"L)ABXEHI$H%.BXK-7/GKgY2eGavG^3CF0-7?GKmX.NBqLC[rY2k-7`IwRBXjCYvCIaX.TBqeC[xT+TCY1IwXS}C-8NBaJT+ZBqkCIgSO<-8TH&GS}IGcm-r^SO]L{MBaPOM]GcsG^@Ne%GcyC[9OM}Bsb-r~MwwHLBGK#Ne,-!KCIsMw2Bsh-sEIu2-!QC[@H$lBsnCI#Iu8-!WC[{G]UCa[BauH$rBs$CI*G]a-!v-sdC@aGe.Ba0CHJGe>-sjC@gBu9RkTBY^-$sXC_CHPBu(RkZBY~-$yRkf-q*E#aM0IGJrE#gSS/-q;D^GL*]GJxJx,Rk4-q[D^ML*}-q|D^SM0Udo;E%8L+DBZgD^rH(}c66DL=Ni!-rPI*zG`,BZmDL^H)D-rVI*5GM2Y4$DL~G`=X:vDMEH)JXBeD`oGM8T.1DMXG`^S\"kD`uGM&SRTDMdC^=RjCCf5IyzOPZH~fCK8NhIN4FH)iMy]Cf#BcrL)%H~lCK&Iw}Cf*C^~H&,H~r-uaG_2Cf;BcxGLlCf[CK.C]8DOU-ugCJrI,`Bc3BbaCgD-um-tMH~)CLGGL=CgJ-u#-tSDOgRm7-tYCgPL.ZBb&D|:L.f-txDO5G}O-vuCgoGO}-v0HSLGPD-x@M;<CNDU7^HSRBe=U7~M;]-w8U8EHSX-w&PC3HSdD)/U8dCiAD)?PC9IA%Jj1PC(Bz:D)`JkbHSwD*APDBIA,D*GJkhBz@D*TJknCiMD*ZD*\"Bz{D*fJk$CiSD*lD+FB0BD*4D+LDQ2D*!D+kCilI3bZulDQ8I3hC}7B0UOWHZurCirI3nU!aB0aOWNT@JME4I3tU!gR!eI3zT@PME!D,QPE~ME)Jl[OW.HUtC}\"PFEM>TI3$OW>GmcJl|Jm9HUzC~FI4sGmiI3+Jm(HU5C~LI4yGmoI3<D.hCkiC~RC\"QIDID,oD.nB2RC~XC\"WCkoD,1eg]-.AJmbCRnB2XC~kCRtCkuI4KZw,-.GC~qY&2B2dD,%U$8-.MC~wT]rDS}D,\"TJaCk,C~/PHgB22Np.OZP-.lNp>Nq~MG\"Np_JpEMHFNp\"I6>HW?I59H<9Go!H;sD:(HW`NqSDByGo)OYpCThCm)H;yBlTB4zNqYHD_Cm:H;4BlZ-:iI5?BlfB45H;!CT/-:oD/yBl4MJhDAh-4\"HZWD/4GX$GrFJoe-5FCpLCSQGX+B6`DAn-5L-<)D/!-5RE=vCSWBn1E=1DAt-5kEGbD/)Bn7J$BCSc-5qEGhDAz-7hEGnD/|GaHE?[DA+-7nEG$D:C-7tDaHCS1Bp|I^.DA<-7+DaNCS7-9(I^>Sca-9/DaTScg-$KDaZScmP}FEI9NsPP}LDasM9~Ke)EI(Sc#Ke:DayM!EE$oIM0NsbE$uN+aM!KU:yIM6I8EP\"nIM$Oa*PRWDcpH=>KhLI{PNs0Jy`CuYHE9E&:IM~H=_D_5CueI8QDL@Dc1HE(Cf8CukH=\"Cf&ELEHE/BzoDc>D;_HSOCu9Jq6BzuM\"GDC(Bz0M\"MI8pCiDIO{CUyBz=Hg*DC/-,UIPBD<FGl`Hg;Bmh-,aDe;CU4GmACw6DC?-,gDe[Bmn-,mB&pCU!B1:Cw$D<e-,5B&vDDNB1@NBoCU|-,#IRdBm+-/2HjMXO,GocDhSXO=-/8CzBSe8-/&B);RwrB4RFA)Se&-:AFA:Rwx-;}EUwNux-<DJ>WM$gDaKEU2Nu3Ct[EU8L]PCt|FDLM$mB%9EU`L]VHgjJHCI!mB%(JHIH@VB%/EW]I!sCwYDo%HHEB&HEW}H@bB)EDo,GY>B)KN_v";
static const char *const s_key = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&()*+,./:;<=>?@[]^_`{|}~\"";

static void find_codeword(size_t index, int pattern[8]) {
  memset(pattern, 0, 8 * sizeof(int));

  const char *start = s_codewords + 3 * index;
  int val = 0;
  for (int i = 0; i < 3; i++) {
    char c = start[i];
    if (c == '-') continue;
    val = val * 91 + (strchr(s_key, c) - s_key);
  }

  for (int i = 6; i >= 0; i--) {
    pattern[i] = val % 6;
    val /= 6;
  }

  int sum = 0;
  for (int i = 0; i < 7; i++) {
    sum += ++pattern[i];
  }
  pattern[7] = 17 - sum;
}

static void make_symbol(const char *input, int mat[8][3]) {
  uint64_t input_int = 0;
  for (int i = 0; i < 16; i++) {
    input_int = input_int * 10 + (input[i] - '0');
  }
  input_int += 10000000000000000; // 1e17

  int codewords[16] = {8, 902};
  for (int i = 7; i >= 2; i--, input_int /= 900) {
    codewords[i] = input_int % 900;
  }

  int ecCodewords[8] = {};
  for (int i = 0; i < 8; i++) {
    int a = (codewords[i] + ecCodewords[7]) % 929;
    for (int j = 6; j >= 0; j--) {
      int x = ecCodewords[j] - (a * (int[]){ 308, 436, 284, 646, 653, 428, 379, 1 }[j]) % 929;
      ecCodewords[j + 1] = x < 0 ? (929 - ((-x) % 929)) : (x % 929);
    }
    ecCodewords[0] = 929 - ((a * 237) % 929);
  }

  for (int i = 7, j = 8; i >= 0; i--, j++) {
    codewords[j] = 929 - (ecCodewords[i] % 929);
  }

  int _mat[8][3] = {
    {  2, codewords[ 0], codewords[ 1] },
    {  7, codewords[ 2], codewords[ 3] },
    {  1, codewords[ 4], codewords[ 5] },
    { 32, codewords[ 6], codewords[ 7] },
    { 37, codewords[ 8], codewords[ 9] },
    { 31, codewords[10], codewords[11] },
    { 62, codewords[12], codewords[13] },
    { 67, codewords[14], codewords[15] },
  };
  memcpy(mat, _mat, sizeof(_mat));
}

static int render_symbol(uint8_t *bytes, int px, int py, int p, int dotw, int doth, int *s, size_t s_length) {
  for (size_t i = 0; i < s_length; i++) {
    int w = s[i];
    if (i & 1) {
      for (int xi = 0; xi < dotw * w; xi++) {
        for (int yi = 0; yi < doth; yi++) {
          int row_offset = 20 * (py + yi);
          int col_offset = px + dotw * p + xi;
          bytes[row_offset + col_offset / 8] |= 1 << (col_offset % 8);
        }
      }
    }
    p += w;
  }
  return p;
}

GBitmap *pdf417_create_bitmap(const char *input) {
  int mat[8][3];
  make_symbol(input, mat);

  uint8_t *bytes = calloc(960, 1);

  const int dotw = 2;
  const int doth = 6;

  int p = 0, px = 0, py = 0;
  for (int row = 0; row < 8; row++) {
    p = 0;
    int r = py + doth * row;

    int start[] = {8, 1, 1, 1, 1, 1, 1, 3};
    p = render_symbol(bytes, px, r, p, dotw, doth, start, ARRAY_LENGTH(start));

    for (int col = 0; col < 3; col++) {
      int codeword = mat[row][col];
      int pattern[8];
      find_codeword(3 * codeword + row % 3, pattern);
      p = render_symbol(bytes, px, r, p, dotw, doth, pattern, ARRAY_LENGTH(pattern));
    }

    int end[] = {1};
    p = render_symbol(bytes, px, r, p, dotw, doth, end, ARRAY_LENGTH(end));
  }

#if PBL_SDK_2
  GBitmap *bitmap = calloc(sizeof(GBitmap), 1);
  bitmap->addr = bytes;
  bitmap->bounds = GRect(0, 0, 138, 48);
  bitmap->is_heap_allocated = 1;
  bitmap->row_size_bytes = 20;
  bitmap->version = 1;
#else
  GBitmap *bitmap = gbitmap_create_blank(GSize(138, 48), GBitmapFormat1Bit);
  gbitmap_set_data(bitmap, bytes, GBitmapFormat1Bit, 20, true);
#endif

  return bitmap;
}
