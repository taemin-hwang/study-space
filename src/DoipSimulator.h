/*
 * DoipSimulator.h
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */

#ifndef SRC_DOIPSIMULATOR_H_
#define SRC_DOIPSIMULATOR_H_

#include <vector>
#include <memory>
#include <string>
#include "transport/ConnectionManager.h"
#include "parser/PresetParser.h"
#include "menu/PopupMenu.h"
#include "menu/MenuItem.h"

using BaseMenuPtr = std::shared_ptr<BaseMenu>;
using PopupMenuPtr = std::shared_ptr<PopupMenu>;
using MenuItemPtr = std::shared_ptr<MenuItem>;

class DoipSimulator {
public:
    DoipSimulator(std::string s);
    virtual ~DoipSimulator();
    void Initialize();
    void Run();
    void Shutdown();
private:
    std::shared_ptr<transport::ConnectionManager> connection_manager_;
    std::unique_ptr<parser::PresetParser> preset_parser_;
    std::shared_ptr<BaseMenu> base_;
};

#endif /* SRC_DOIPSIMULATOR_H_ */
