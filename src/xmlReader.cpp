//============================================================================
// Name        : xmlReader.cpp
// Author      : Jan Schiefer
// Version     : 0.1
// Copyright   : GNU General Public License (GPL)
// Description : A quick and easy test program for squishyXML
//============================================================================

#include <iostream>
#include <squishyXML.hpp>

using namespace std;

int main() {

	squishyXMLParser parser;

	std::string_view filename ("mp-test.xml");

	squishyXMLContext myContext;

	squishyXMLDocument doc( myContext, filename, std::string_view("") , XML_PARSE_DTDATTR );


	if (doc.ptr == NULL) cout << "Failed to parse " << filename << endl;
	else if (myContext.ptr->valid == 0) cout << "Failed to validate " << filename << endl;
	else {
		cout << "XML File sucessfuly loaded:    " << filename << endl;
	}

	std::string doc_string;

	squishyXMLNode rootElement;

	if( doc.getRootElement( rootElement ) ) cout << "Successfully got root element." << endl;

	std::string theProperty;

	rootElement.getNodeProperty( "U", theProperty );

	cout << "Node property: " << theProperty << endl;

	squishyXMLNode childElement;

	if( rootElement.findSingleNodeByName( "P", childElement , true ) ) cout << "Successfully got child element." << endl;

	std::string childAttr1;

	if ( childElement.getNodeProperty("g", childAttr1 ) ) cout << "Successfully got child 1 attribute." << endl;

	cout << "Child element 1 attribute: " << childAttr1 << endl;

	std::vector<squishyXMLNode> vector_childElements;

	if( rootElement.findNodesByName( "A", vector_childElements , true ) )cout << "Successfully got child elements to vector." << endl;

	std::string childAttr2;

	if ( vector_childElements.front().getNodeProperty("n", childAttr2 ) ) cout << "Successfully got child 2 attribute." << endl;

	cout << "Child element 2 attribute: " << childAttr2 << endl;

	if( childElement.setNodeContent( "TEST CONTENT ") ) cout << "Successfully set child node 1 content." << endl;

	if( vector_childElements.front().setNodeProperty( "TEST" , "ATTRIBUTE") ) cout << "Successfully set child node 2 property." << endl;

	std::unordered_map <std::string, std::string> test_properties = {
	        {"RED","#FF0000"},
	        {"GREEN","#00FF00"},
	        {"BLUE","#0000FF"}
	    };

	if( vector_childElements.front().setNodeProperties( test_properties ) ) cout << "Successfully set child node 2 properties as map." << endl;


	squishyXMLNode singleNode( NULL, "TESTNODE");

	singleNode.setNodeContent("My Content");

	if(	rootElement.addChildNode ( singleNode ) ) cout << "Successfully added single child node." << endl;

	doc.printDocToString(doc_string, "", true, false);

	cout << doc_string << endl;
	cout << endl;

	if( doc.printDocToFile( "test_output.xml" , "",  true, false) ) cout << "Successfull XML file output." << endl;

	return 0;
}
