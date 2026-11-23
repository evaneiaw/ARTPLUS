# StepAndRepeatCAD.dll — triagem automatica

- Gerado: 2026-11-19 03:28
- Caminho: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\StepAndRepeatCAD.dll`
- Tamanho: 458792 bytes
- SHA-256: `faa143db101aade9d178cdaa85cf472a3b60c1fea08f28934426c3e2f2046882`
- Arquitetura: x64
- DIE: PE64: Linker: Microsoft Linker(14.41.34435); Compiler: Microsoft Visual C/C++(19.41.34435)[C++]; Library: Microsoft C/C++ Runtime[dynamic]; Library: Xerces-C++ XML Parser
- Strings: 1441 capturadas; amostra em `rag/sources/StepAndRepeatCAD.strings.txt`

## Secoes

| Secao | VA | VSize | RawSize | Entropia |
|---|---|---|---|---|
| .text | 0x1000 | 276551 | 276992 | 6.191 |
| .rdata | 0x45000 | 122034 | 122368 | 5.639 |
| .data | 0x63000 | 39488 | 32256 | 4.897 |
| .pdata | 0x6D000 | 11088 | 11264 | 5.473 |
| .rsrc | 0x70000 | 480 | 512 | 4.709 |
| .reloc | 0x71000 | 3024 | 3072 | 5.393 |

## Strings de interesse (amostra)

- `Unknown error (%d)`
- `No message text available for error %d`
- `asio.misc error`
- `StepAndRepeatCADTask.Error.XMLNoFileOrProduct`
- `StepAndRepeatCADTask.Error.XMLInvalidLastPage`
- `StepAndRepeatCADTask.Error.XMLNoFileInProduct`
- `StepAndRepeatCADTask.Error.XMLMissingJobKey`
- `StepAndRepeatCADTask.Error.XMLMissingRunListItemKey`
- `StepAndRepeatCADTask.Error.XMLParsingError`
- `StepAndRepeatCADTask.Error.XMLFatalParsingError`
- `StepAndRepeatCADTask.Error.XMLXercesInitialization`
- `StepAndRepeatCADTask.Error.XMLParsingBadFile`
- `StepAndRepeatCADTask.Error.ZeroTotalQuantity`
- `StepAndRepeatCADTask.Error.TooManyInputFiles`
- `StepAndRepeatCADTask.Error.TooManyXmlInputFiles`
- `StepAndRepeatCADTask.Error.MixedDuplexEntriesInXML`
- `StepAndRepeatCADTask.Error.MixedDuplexEntriesInInputFiles`
- `StepAndRepeatCADTask.Error.InvalidSheetSize`
- `StepAndRepeatCADTask.Error.InvalidPlateSize`
- `StepAndRepeatCADTask.Error.CADLayoutIsOutsidePlate`
- `StepAndRepeatCADTask.Error.SheetIsOutsidePlate`
- `StepAndRepeatCADTask.Error.InvalidShrinkValues`
- `StepAndRepeatCADTask.Error.CannotDistributeOneUps`
- `StepAndRepeatCADTask.Error.CannotPlaceInputFile`
- `StepAndRepeatCADTask.Error.CannotOpenTemplate`
- `StepAndRepeatCADTask.Error.XMLNoSuchFile`
- `StepAndRepeatCADTask.Warning.PDFPlusDuplexTemplate`
- `StepAndRepeatCADTask.Warning.PDFPlusTemplateHasMorePages`
- `Template separations:`
- `Output separations:`
- `Error found in`
- `Error occured when getting Product part parameters for file`
- `Looking for die shape using separation "`
- `StepAndRepeatCADTask.Error.CannotMatch1UpWithAnyStationGroup`
- `StepAndRepeatCADTask.Error.StationGroupIsEmpty`
- `ERROR: Product-part parameter Side was not used correctly to define valid duplex job.`
- `ERROR: Product has 2 parts but product-part parameter Side was not used to define valid duplex job.`
- `ERROR: Too many input files based on product. Use XML input to specify more complex front/back combinations.`
- `Front separations:`
- `Back separations:`
- `esko:snr_back_`
- `ProfileMarks :`
- `StepAndRepeatCADTask.Error.SplitOutputNotSupportedInDuplexMode`
- `StepAndRepeatCADTask.Error.MissingDuplexInput`
- `StepAndRepeatCADTask.Warning.BackMarkSetUsedInSimplexMode`
- `StepAndRepeatCADTask.Warning.PDFPlusTemplateBackNotTurned`
- `StepAndRepeatCADTask.Warning.PDFPlusTemplateBackNotTumbled`
- `StepAndRepeatCADTask.Error.OnlyOneStationGroupSupportedInTemplate`
- `StepAndRepeatCADTask.Error.NoStationsInTemplate`
- `StepAndRepeatCADTask.Error.FailedProcessingTheSeparateBackgroundFile`
- `StepAndRepeatCADTask.Stage.PreparingMarks`
- `StepAndRepeatCADTask.Message.PreparingMarks`
- `StepAndRepeatCADTask.Error.TemplateContainsPlateIDMark`
- `StepAndRepeatCADTask.Error.MarksetContainsPlateIDMark`
- `StepAndRepeatCAD.dll`
- `??0InputFile@StepAndRepeatCAD@@QEAA@AEBVpath@filesystem@boost@@AEBV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@@Z`
- `??AStationGroup@StepAndRepeatCAD@@QEAAPEAVStation@DocumentStructuralDesign@@_K@Z`
- `?ApplyMarkSetOnSheet@StepAndRepeatCAD@@YA_NAEAVPage@ArtDoc@@AEAV?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@@Z`
- `?CloneBackPage@StepAndRepeatCAD@@YAAEAVPage@ArtDoc@@AEAVDocument@3@AEBV23@W4DuplexType@1@@Z`
- `?CollectStations@StepAndRepeatCAD@@YA?AV?$vector@PEAVStation@DocumentStructuralDesign@@V?$allocator@PEAVStation@DocumentStructuralDesign@@@std@@@std@@AEAVPage@ArtDoc@@@Z`
- `?CollectUsedSeparations@StepAndRepeatCAD@@YA?AV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@AEAV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@st`
- `?ComputeUsedSeparations@InputFile@StepAndRepeatCAD@@QEAAXAEAV?$map@Vpath@filesystem@boost@@V?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@U?$less@Vpath@filesystem@boost@@@5@V?$allo`
- `?CreateDocumentFromTemplate@StepAndRepeatCAD@@YA?AV?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@AEBVpath@filesystem@boost@@0AEBUProcessingParams@1@PEBUPageBoxParams@1@AEAVTaskReporter@Do`
- `?CreateNewTemplate@StepAndRepeatCAD@@YA?AV?$unique_ptr@VDocument@ArtDoc@@U?$default_delete@VDocument@ArtDoc@@@std@@@std@@AEBVpath@filesystem@boost@@0AEBUProcessingParams@1@AEAUPageBoxParams@1@AEAVTaskReporter@DocumentMar`
- `?DistributeInputs@StepAndRepeatCAD@@YA?AV?$vector@PEAVInputFile@StepAndRepeatCAD@@V?$allocator@PEAVInputFile@StepAndRepeatCAD@@@std@@@std@@AEAV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCA`
- `?DistributeInputsVDP@StepAndRepeatCAD@@YA?AU?$pair@V?$vector@PEAVInputFile@StepAndRepeatCAD@@V?$allocator@PEAVInputFile@StepAndRepeatCAD@@@std@@@std@@V?$vector@_KV?$allocator@_K@std@@@2@@std@@AEAV?$vector@VInputFile@Step`
- `?DumpSeparations@StepAndRepeatCAD@@YAXAEAV?$basic_ostream@DU?$char_traits@D@std@@@std@@AEBV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@3@@Z`
- `?DuplexStepAndRepeat@StepAndRepeatCAD@@YA_NAEBUProcessingParams@1@AEAUPageBoxParams@1@AEAV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEBVpath@filesystem@boost@@AEAW4Templa`
- `?FindDesignInInputs@StepAndRepeatCAD@@YA_NAEAV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEAVDocument@ArtDoc@@_N2@Z`
- `?GetTaskInputs@StepAndRepeatCAD@@YA?AV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEBVBG_TArray@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@_NAEAVP_TProx`
- `?GetTaskInputsFromXML@StepAndRepeatCAD@@YA?AV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEBVpath@filesystem@boost@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D`
- `?GetTemplateStationsCount@StepAndRepeatCAD@@YAHAEBVpath@filesystem@boost@@AEBUProcessingParams@1@AEAVTaskReporter@DocumentMarks@@@Z`
- `?MergeHalftonesFromInputFiles@StepAndRepeatCAD@@YAXAEBV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEAVDocument@ArtDoc@@@Z`
- `?PopulateSheetWith1Up@StepAndRepeatCAD@@YA_NAEAVPage@ArtDoc@@AEBVpath@filesystem@boost@@AEAV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEAVTaskReporter@DocumentMarks@@W4Te`
- `?PopulateSheetWithVDP@StepAndRepeatCAD@@YA_NAEAVPage@ArtDoc@@_K1AEBVpath@filesystem@boost@@AEAV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEAVTaskReporter@DocumentMarks@@W`
- `?ReadSeparations@InputFile@StepAndRepeatCAD@@AEAAXAEBVpath@filesystem@boost@@AEAV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@AEA_K@Z`
- `?SetBackFileName@InputFile@StepAndRepeatCAD@@QEAAXAEBVpath@filesystem@boost@@AEBV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@@Z`
- `?SetFileName@InputFile@StepAndRepeatCAD@@QEAAXAEBVpath@filesystem@boost@@AEBV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@@Z`
- `?SplitStations@StepAndRepeatCAD@@YA?AV?$vector@UStationGroup@StepAndRepeatCAD@@V?$allocator@UStationGroup@StepAndRepeatCAD@@@std@@@std@@AEAV?$vector@PEAVStation@DocumentStructuralDesign@@V?$allocator@PEAVStation@Document`
- `?UsedSeparations@InputFile@StepAndRepeatCAD@@QEAAAEBV?$vector@VEntry@Separation@ArtDoc@@V?$allocator@VEntry@Separation@ArtDoc@@@std@@@std@@_N@Z`
- `?VDPStepAndRepeat@StepAndRepeatCAD@@YA_NAEBUProcessingParams@1@AEAUPageBoxParams@1@AEAV?$vector@VInputFile@StepAndRepeatCAD@@V?$allocator@VInputFile@StepAndRepeatCAD@@@std@@@std@@AEBVpath@filesystem@boost@@3AEAW4Template`
- `BGMWare.dll`
- `?CreateStationMask@DocumentLayout@@YA?AU?$pair@V?$shared_ptr@$$CBVCompound@YAGL@@@std@@V?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@std@@AEBV?$shared_ptr@$$CBVFormPaint@ArtPaint@@@3@AEBV?$variant@W4StationM`
- `DocumentLayout.dll`
- `?GetFormInstance@Station@DocumentStructuralDesign@@UEAAPEAVPath@ArtDoc@@XZ`
- `?GetStationMask@Station@DocumentStructuralDesign@@UEBA?AV?$shared_ptr@$$CBVCompound@YAGL@@@std@@XZ`
- `?GetClippingObject@Station@DocumentStructuralDesign@@QEAAPEAVContentObject@ArtDoc@@XZ`
- `?GetStationInfo@Station@DocumentStructuralDesign@@UEBA?AUStationInfo@2@XZ`
- `?GetPrintSide@Station@DocumentStructuralDesign@@UEBA?AW4PrintSide@2@XZ`
- `?SetBleedDistance@Station@DocumentStructuralDesign@@QEAAXAEBV?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@Z`
- `?SetOverlapBleedDistance@Station@DocumentStructuralDesign@@QEAAXAEBV?$optional@V?$CoordinateBase@UMilliPointCoordinateSystem@YAGL@@$00@YAGL@@@std@@@Z`
- `?CalculateReplacementTrafo@Station@DocumentStructuralDesign@@QEBA?AV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@V?$shared_ptr@$$CBVFormPaint@ArtPaint@@@std@@_N@Z`
- `?ResolveStationBleedOverlaps@DocumentStructuralDesign@@YAXAEAVContent@ArtDoc@@@Z`
- `?CopyStations@DocumentStructuralDesign@@YAXAEBVContent@ArtDoc@@AEAV23@W4PrintSide@1@AEBV?$TransformationBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@@Z`
- `?SetStructuralDesignLayerName@DocumentStructuralDesign@@YAXAEAVReadOptions@ArtDoc@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z`
- `?SetRepetitionLayerName@DocumentStructuralDesign@@YAXAEAVReadOptions@ArtDoc@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z`
- `?SetImportedTextObjectsLayerName@DocumentStructuralDesign@@YAXAEAVReadOptions@ArtDoc@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z`
- `?SetImportedStructuralLinesLayerName@DocumentStructuralDesign@@YAXAEAVReadOptions@ArtDoc@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z`
- `?SetImportProfileForStructuralLinesOnOpening@DocumentStructuralDesign@@YAXAEAVReadOptions@ArtDoc@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z`
- `?SetIncludeStructuralLinesFromOneUp@DocumentStructuralDesign@@YAXAEAVReadOptions@ArtDoc@@_N@Z`
- `?GetMainDesignBounds@Object@DocumentStructuralDesign@@QEBA?AV?$RectangleBase@UMilliPointCoordinateSystem@YAGL@@@YAGL@@XZ`
- `?GetPrintItems@Object@DocumentStructuralDesign@@QEBAAEBV?$vector@UPrintItem@DocumentStructuralDesign@@V?$allocator@UPrintItem@DocumentStructuralDesign@@@std@@@std@@XZ`
- `?GetPrintItemIndex@Object@DocumentStructuralDesign@@QEBA?AV?$optional@_K@std@@XZ`
- `?GetLink@Object@DocumentStructuralDesign@@QEBAAEBULink@2@XZ`
- `??1?$ConstVisitor@VObject@DocumentStructuralDesign@@@ArtDoc@@MEAA@XZ`
- `??0?$ConstVisitor@VObject@DocumentStructuralDesign@@@ArtDoc@@QEAA@XZ`
- `?EndVisit@?$ConstVisitor@VObject@DocumentStructuralDesign@@@ArtDoc@@UEAAXAEBVObject@DocumentStructuralDesign@@@Z`
- `?SetStationOrderIndex@DocumentStructuralDesign@@YAXAEAVStation@1@V?$optional@_K@std@@@Z`
- `?GetStationOrderIndex@DocumentStructuralDesign@@YA?AV?$optional@_K@std@@AEBVStation@1@@Z`
- `??1?$Visitor@VStation@DocumentStructuralDesign@@@ArtDoc@@MEAA@XZ`
- `??0?$Visitor@VStation@DocumentStructuralDesign@@@ArtDoc@@QEAA@XZ`
- `?EndVisit@?$Visitor@VStation@DocumentStructuralDesign@@@ArtDoc@@UEAAXAEAVStation@DocumentStructuralDesign@@@Z`
- `?EnableRegenerationHub@DocumentStructuralDesign@@YAXAEAVDocument@ArtDoc@@_N@Z`
- `DocumentStructuralDesign.dll`
- `BGTypes.dll`
- `?UpdateMarksOnPage@DocumentMarks@@YAXAEAVPage@ArtDoc@@@Z`
- `?CopyMarksToPage@DocumentMarks@@YA_NAEBVPage@ArtDoc@@AEAV23@_NPEAV?$set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@`
- `?CopyPageWithMarks@DocumentMarks@@YA_NAEAVPage@ArtDoc@@0AEAVCloneStrategy@3@_N@Z`
- `?DeleteMarks@DocumentMarks@@YAXAEAVPage@ArtDoc@@_N@Z`
- `?EnableUpdates@DynamicMarksController@DocumentMarks@@QEAA_N_N@Z`

## Lacunas

- funcoes/xrefs: aguardando export do Ghidra

