﻿#include "UpdateBlockFromOtherFile.hpp"

namespace sstd {

	extern void loadUpdateBlockFromOtherFile() { UpdateBlockFromOtherFile::load(); }

	void UpdateBlockFromOtherFile::load() {
		arx_add_main_command<UpdateBlockFromOtherFile>();
	}

	void UpdateBlockFromOtherFile::main() {
		Acad::ErrorStatus varAError;
		constexpr const auto varOtherFileName = LR"(E:\Duty\Duty\template\template.all.dwg)"sv;
		constexpr const auto varBlockName = LR"(横边框2(G3000))"sv;
		constexpr const auto varTargetFileName = LR"(E:\Duty\Duty\template\template.all.1.dwg)"sv;
		
		std::unique_ptr<AcDbDatabase> varTargetFile{ new AcDbDatabase{ false } };
		if (Acad::eOk != varTargetFile->readDwgFile(varTargetFileName.data(),
			AcDbDatabase::kForReadAndWriteNoShare)) {
			acutPrintf(LR"(打开文件")");
			acutPrintf(varTargetFileName.data());
			acutPrintf(LR"("失败
)");
			return;
		}
		else {
			acutPrintf(LR"(打开文件")");
			acutPrintf(varTargetFileName.data());
			acutPrintf(LR"("成功
)");
		}

		std::unique_ptr<AcDbDatabase> varOtherFile{ new AcDbDatabase{false} };
		if (Acad::eOk != varOtherFile->readDwgFile(varOtherFileName.data())) {
			acutPrintf(LR"(打开文件")");
			acutPrintf(varOtherFileName.data());
			acutPrintf(LR"("失败
)");
			return;
		}			

		{
			auto document = acDocManager->document(varTargetFile.get());
			acDocManager->lockDocument(document);
			acDocManager->setCurDocument(document, AcAp::kNone, false);
			AcDbObjectId varBlockID;
			if ( (varAError=varTargetFile->insert(varBlockID,
				varBlockName.data(),
				varBlockName.data(),
				varOtherFile.get(),
				false))!=Acad::eOk) {
				acutPrintf(LR"(插入块失败:)");
				acutPrintf( acadErrorStatusText(varAError) );
				acutPrintf(LR"(
)");
				acDocManager->unlockDocument(document);
				return;
			}
			acDocManager->unlockDocument(document);
		}

		if (Acad::eOk != varTargetFile->save()) {
			acutPrintf(LR"(保存文件失败
)");
			return;
		}
		else {
			acutPrintf(LR"(保存文件成功
)");
		}
		
	}/*UpdateBlockFromOtherFile::main*/

	UpdateBlockFromOtherFile::UpdateBlockFromOtherFile() {

	}

}/*namespace sstd*/


