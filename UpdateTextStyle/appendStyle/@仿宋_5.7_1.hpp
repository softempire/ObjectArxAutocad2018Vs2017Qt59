﻿varAns.emplace(LR"(@仿宋_5.7_1)"sv, ApplyMaps::value_type::second_type{
[](simple_code_args) {
sstd::ArxClosePointer<AcDbTextStyleTableRecord> varLocalR;
if (argR == nullptr) {
	argR = new AcDbTextStyleTableRecord;
	varLocalR = argR;
	argR->setName(argNM.data());
	argTST->add(argR);
}

argR->setFlagBits(argR->flagBits()&0b11111001)/*清除标志位*/;
argR->setIsShapeFile(false);
argR->setFileName(LR"(simfang.ttf)")/*shx字体文件名*/;
//argR->setBigFontFileName(LR"(whtmtxt.shx)")/*shx大字体文件名*/;

auto varSetTextHeight = [argR]() {
	argR->setTextSize(5.7)/*文字高度*/;
	if (argR->priorSize() < 5) {
		argR->setPriorSize(5.7)/*默认大小*/;
	}
};

if constexpr(Version == 0) {
	varSetTextHeight();
}
else {
	if (varLocalR) {
		varSetTextHeight();
	}
}

argR->setXScale(1.0)/*宽度比*/;
setAnnotative(argR,true)/*注释性*/;

},false });


