#include "testApp.h"
#include "loadUrl.h"

// we need to include the RegularExpression
// header file and say that we are using that
// name space
#include "Poco/RegularExpression.h"
using Poco::RegularExpression;


void findandreplace( std::string& tInput, std::string tFind, std::string tReplace ) {
	size_t uPos = 0;
	size_t uFindLen = tFind.length();
	size_t uReplaceLen = tReplace.length();
    
	if( uFindLen == 0 ){
		return;
	}
    
	for( ;(uPos = tInput.find( tFind, uPos )) != std::string::npos; ){
		tInput.replace( uPos, uFindLen, tReplace );
		uPos += uReplaceLen;
	}
    
}


vector < string > getMatchedStrings (string contents, string regex );
vector < string > getMatchedStrings (string contents, string regex ){
    
    vector < string > results;
    RegularExpression regEx(regex);
    RegularExpression::Match match;
    
    while(regEx.match(contents, match) != 0) {
        
        // we get the sub string from the content
        // and then trim the content so that we
        // can continue to search
        string foundStr = contents.substr(match.offset, match.length);
        contents = contents.substr(match.offset + match.length);
        
        results.push_back(foundStr);
        
    }
    return results;
}

//--------------------------------------------------------------
void testApp::setup(){

    
    results = new unsigned char[809600];
   
    temp = ofBufferFromFile("BVpfFkYIMAAZ0V6.jpg" );
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    tempImg.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    int len = 0;
    test((unsigned char *)temp.getBinaryBuffer(), (int)temp.size(), results, len);

    
    RegularExpression regEx("semelhantes");
    RegularExpression::Match match;
    string temp = string((char *) results);
    match.offset = 0;
    if (regEx.match(temp, match.offset, match))
    {
        int pt = match.offset;
        bool bKeep = true;
        int firstQuote = -1;
        int secondQuote = -1;
        while(bKeep){
            
            if (temp[pt] == '"'){
                if (secondQuote != -1) firstQuote = pt;
                else secondQuote = pt;
                
                cout << " " << firstQuote << " " << secondQuote << endl;
            }
            if (temp[pt] == '<'){
                bKeep = false;
                break;
            }
            pt--;
        }
        cout << pt << " " << match.offset << endl;
        string url = temp.substr(firstQuote+1, secondQuote - firstQuote - 1);
        //cout << url <<endl;
        
        findandreplace(url, "&amp;", "&");
        
        
        string fileName = ofToDataPath("out.txt");
        
        string command = "curl -L -A \"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.94 Safari/537.4\" \"http://google.com" + url + "\" > " + fileName;
        
        system(command.c_str());
        
        
        //cout << url << endl;
    }
    
    ofBuffer newFile = ofBufferFromFile("out.txt");
   
    //newFile.getText();
    
    
    //RegularExpression regEx2("imgrefurl.*?&amp;");
    //RegularExpression::Match match2;
   
    
    vector < string > str = getMatchedStrings(newFile.getText(), "imgurl.*?&amp;");
    
    for (int i = 0; i < str.size(); i++){
        
        str[i] = str[i].substr(7, str[i].size() - 7 - 5);
        cout << str[i] << endl;
        
        
    }
    

    tempImg.loadImage(str[0]);
    
    

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    
    // <a.*?Imagens visualmente semelhantes</a>
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

    
    
    string fileName = dragInfo.files[0];
    
    ofDisableDataPath();
    temp = ofBufferFromFile(fileName);
    ofEnableDataPath();
    
    keyPressed(' ');
    
    
    
    
    
}