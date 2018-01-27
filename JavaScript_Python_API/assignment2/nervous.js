//initial setup
var url = 'http://127.0.0.1:8080';

var bubble1 = document.getElementById('bubble1');
var bubble2 = document.getElementById('bubble2');
var bubble3 = document.getElementById('bubble3');
var bubble4 = document.getElementById('bubble4');

var p1 = document.getElementById('p1');
var p2 = document.getElementById('p2');
var p3 = document.getElementById('p3');
var p4 = document.getElementById('p4');

var firstTime = true;
var firstTime2 = true;
var firstTime3 = true;
var firstTime4 = true;
var firstTime5 = true;

var bubble1ClassName = bubble1.className;

var messageCounter = 0;

var counter = 1;
var counterLastTime = true;


//prompt for path and set url
var button = document.getElementById('submit');
var path = window.prompt("Please enter a path name:");
if(path != '/' && path != ''){
    if(path[0] == '/'){path = path.slice(1);}
    url = url + '/' + path;
}





//showtime
window.onload = function(){fetch(url).then(checkstatus)};





//"Gretchen, stop trying to make fetch happen! It's not going to happen!" -Regina George
button.onclick = function(){
    
    //grab textbox contents and encode
    var postText = document.getElementById('postbox').value;
    var postTextEncoded = encodeURIComponent(postText);
    console.log(postTextEncoded);
    
    //fetch POST
    fetch(url,{
        method: "POST",
        body: "messages=" + postTextEncoded,
        mode: "no-cors",
        headers: {
            "Content-Type": 'application/x-www-form-urlencoded'
        }
    });
    
    //fetch GET
    fetch(url)
    .then((resp) => resp.json())
    .then(function(data){
        shifty();
        posty(data);
    });
    
    
}





//function to check status of server
var checkstatus = function(response) {
    if (response.status >= 200 && response.status < 300) {
        console.log("Status code good.");
    } else {
        console.log("Status code not good.")
        window.location.href = "404.html";
    }
}





//shift the bubbles
var shifty = function(){
    
    //everythins is dependant on bubble1
    if(bubble1ClassName == "hide"){
        bubble1ClassName = "show1";
        bubble1.className = "show1";
        
        bubble2.style.top = "395px";
        bubble2.className = "hide";
        
        if(firstTime == false){
            bubble3.style.top = "25px";
            bubble3.className = "show4";
            
            bubble4.style.top = "150px";
            bubble4.className = "show3";
        }
        
        firstTime = false;
        
        return;
    }else if (bubble1ClassName == "show1"){
        bubble1.style.top = "350px";
        bubble1.className = "show2";
        bubble1ClassName = "show2";
        
        bubble2.style.top = "395px";
        bubble2.className = "show1";

        bubble3.style.top = "395px";
        bubble3.className = "hide";
        
        if(firstTime2 == false){
            bubble4.style.top = "25px";
            bubble4.className = "show4";
        }
        
        firstTime2 = false;
        
        return;
    }else if (bubble1ClassName == "show2"){
        bubble1.style.top = "150px";
        bubble1.className = "show3";
        bubble1ClassName = "show3";
        
        bubble2.style.top = "350px";
        bubble2.className = "show2";
        
        bubble3.style.top = "395px";
        bubble3.className = "show1";
        
        if(firstTime3 == false){
            bubble4.style.top = "385px";
            bubble4.className = "hide";
        }
        
        firstTime3 = false;
        
        return;
    }else if (bubble1ClassName == "show3"){
        bubble1.style.top = "25px";
        bubble1.className = "show4";
        bubble1ClassName = "show4";
        
        bubble2.style.top = "150px";
        bubble2.className = "show3";
        
        bubble3.style.top = "350px";
        bubble3.className = "show2";
        
        bubble4.style.top = "395px";
        bubble4.className = "show1";
            
        return;
    }else if (bubble1ClassName == "show4"){
        bubble1.style.top = "385px";
        bubble1.className = "hide";
        bubble1ClassName = "hide";
        
        bubble2.style.top = "25px";
        bubble2.className = "show4";
        
        bubble3.style.top = "150px";
        bubble3.className = "show3";
        
        bubble4.style.top = "350px";
        bubble4.className = "show2";
        
        return;
    }   
}

//function that takes care of the bubble text
var posty = function(data){
    if(counter == 1){
        p1.innerHTML = data[messageCounter];
        p1.className = "show1";
        
        if(firstTime4 == false){
            p2.className = "hide";
            p2.style.top = "460px";
            
            p3.style.top = "100px";
            p3.className = "show4";
            
            p4.style.top = "225px";
            p4.className = "show3"; 
        }
        
        firstTime4 = false;
        counterLastTime = false;
    }else if(counter == 2){
        p2.innerHTML = data[messageCounter];
        p2.className = "show1";        
        
        p1.style.top = "425px";
        p1.className = "show2";
        
        if(firstTime5 == false){
            p3.className = "hide";
            p3.style.top = "460px";

            p4.style.top = "100px";
            p4.className = "show4";
        }
        
        firstTime5 = false;
    }else if(counter == 3){
        p3.innerHTML = data[messageCounter];
        p3.className = "show1";
        
        p1.style.top = "225px";
        p1.className = "show3";
        
        p2.style.top = "425px";
        p2.className = "show2";

        p4.className = "hide";
        p4.style.top = "460px";
    }else if(counter == 4){
        p4.innerHTML = data[messageCounter];
        p4.className = "show1";
        
        p1.style.top = "100px";
        p1.className = "show4";
        
        p2.style.top = "225px";
        p2.className = "show3";
        
        p3.style.top = "425px";
        p3.className = "show2";
    }else{
        p1.className = "hide";
        p1.style.top = "460px";
        
        p2.style.top = "100px";
        p2.className = "show4";
        
        p3.style.top = "225px";
        p3.className = "show3"; 

        p4.style.top = "425px";
        p4.className = "show2";

        counter = 1;
        counterLastTime = true;
    }
    if(counterLastTime == false){
        counter++;
    }
        messageCounter++;
}