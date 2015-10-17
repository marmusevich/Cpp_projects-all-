#include <iostream>
#include <sstream>
#include "pugixml.hpp"

using namespace std;


int g_keyLeft = 0x25;
int g_keyRight = 0x27;
int g_keyFire = 0x20;

bool SaveGameConfig(string config= "config.xml")
{
	pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(config.c_str());

	if (!result)
		return false; // Ошибка парсинга данных


    pugi::xml_node nodeTools = doc.child("Tools");
	// ищем нужные нам XML-ноды
	pugi::xml_node nodeLeft = nodeTools.child("left");
	pugi::xml_node nodeRight = nodeTools.child("right");
	pugi::xml_node nodeFire = nodeTools.child("fire");

    nodeTools.set_value("1");


    cout << doc.last_child().set_value("useless comment");
    //nodeFire.append_child(pugi::node_pcdata).set_value("0x01");
    nodeFire.set_value("0x01");
    //nodeFire.child.set_value("0x01");
/*
    pugi::xml_node node = nodeTools.append_child("node");

    // add description node with text child
    pugi::xml_node descr = node.append_child("description");
    descr.append_child(pugi::node_pcdata).set_value("Simple node");

    // add param node before the description
    pugi::xml_node param = node.insert_child_before("param", descr);

    // add attributes to param node
    param.append_attribute("name") = "version";
    param.append_attribute("value") = 1.1;
    param.insert_attribute_after("type", param.attribute("name")) = "float";
*/

    doc.save_file(config.c_str());

	return true;
}


bool LoadGameConfig(string config= "config.xml")
{
	pugi::xml_document doc;

	//pugi::xml_parse_result result = doc.load_buffer_inplace((void*)config.c_str(), config.length());


    pugi::xml_parse_result result = doc.load_file(config.c_str());

	if (!result)
		return false; // Ошибка парсинга данных


    pugi::xml_node nodeTools = doc.child("Tools");
	// ищем нужные нам XML-ноды
	pugi::xml_node nodeLeft = nodeTools.child("left");
	pugi::xml_node nodeRight = nodeTools.child("right");
	pugi::xml_node nodeFire = nodeTools.child("fire");

    cout <<"nodeLeft ="<<nodeLeft << endl;
    cout <<"nodeTools ="<<nodeTools << endl;
    cout <<"nodeRight ="<<nodeRight << endl;
    cout <<"nodeFire ="<<nodeFire << endl;


	// load defaults
	g_keyLeft = 0x25;
	g_keyRight = 0x27;
	g_keyFire = 0x20;

	// читаем конфиг из XML-нод
	if (nodeLeft)
		stringstream(nodeLeft.child_value()) >>std::hex >>g_keyLeft;
	if (nodeRight)
		stringstream(nodeRight.child_value()) >>std::hex >>g_keyRight;
	if (nodeFire)
		stringstream(nodeFire.child_value()) >>std::hex >>g_keyFire;

	return true;
}


// save document to file
//std::cout << "Saving result: " << doc.save_file("save_file_output.xml") << std::endl;




int main()
{

// TODO (леша#1#): test todo
   	const std::string config = "config.xml";

    cout <<"g_keyLeft ="<<g_keyLeft << endl;
    cout <<"g_keyRight ="<<g_keyRight << endl;
    cout <<"g_keyFire ="<<g_keyFire << endl;
    LoadGameConfig(config);
    cout <<"g_keyLeft ="<<g_keyLeft << endl;
    cout <<"g_keyRight ="<<g_keyRight << endl;
    cout <<"g_keyFire ="<<g_keyFire << endl;

    SaveGameConfig(config);

        return 0;
}
