//initial setup
var url = 'http://127.0.0.1:8080/register';

var allEmails;

var registration = document.getElementById('registration');

var firstName = document.getElementById('firstName');
var firstNameTextBox = "";
var lastName = document.getElementById('lastName');
var lastNameTextBox = "";
var email = document.getElementById('email');
var emailTextBox = "";
var clearTextPassword = document.getElementById('clearTextPassword');
var clearTextPasswordTextBox = "";
var registerButton = document.getElementById('registerButton');

var loginEmail = document.getElementById('loginEmail');
var loginEmailTextBox = "";
var loginPassword = document.getElementById('loginPassword');
var loginPasswordTextBox = "";
var loginButton = document.getElementById('loginButton');

var buttons = document.getElementById('buttons')





//showtime - this fetch grabs all the emails for registration verification
window.onload = function(){
                    fetch(url,{
                        method: "GET",
                        credentials: "include"
                    })
                        .then((resp) => resp.json())
                        .then(function(data){
                            allEmails = data;
                    })
}





//registerButton
registerButton.onclick = function(){
    firstNameTextBox = firstName.value;
    lastNameTextBox = lastName.value;
    emailTextBox = email.value;
    clearTextPasswordTextBox = clearTextPassword.value;
    
    var body = "firstName="          + encodeURIComponent(firstNameTextBox) + 
               "&lastName="          + encodeURIComponent(lastNameTextBox) +  
               "&email="             + encodeURIComponent(emailTextBox) +  
               "&clearTextPassword=" + encodeURIComponent(clearTextPasswordTextBox);        
    
    //this for loop verifies email uniqness on client side
    for(i = 0; i < allEmails.length; i++){
        if(allEmails[i].includes(emailTextBox)){
            alert("That email is already in use. Please choose another one.")
            return;
        }
    }
    
    fetch(url,{
        method: "POST",
        body: body,
        mode: "cors",
        credentials: "include",
        headers: {
            "Content-Type": 'application/x-www-form-urlencoded'
        }
    });
    
    //switch over to assignment3 stuff
    registration.style.display = "none";
    buttons.style.display = "flex";
    
    var javaScript2 = document.createElement("script");
    javaScript2.src = "brains.js";
    javaScript2.type = "text/javascript";
    javaScript2.id = "script2";
    document.getElementsByTagName("body")[0].appendChild(javaScript2);
    document.getElementById('script').removeElement;
    
    //
}





//loginButton
loginButton.onclick = function(){
    
    url = 'http://127.0.0.1:8080/login'
    
    loginEmailTextBox = loginEmail.value;
    loginPasswordTextBox = loginPassword.value;
    
    
    var body = "loginEmail="             + encodeURIComponent(loginEmailTextBox) +  
               "&loginClearTextPassword=" + encodeURIComponent(loginPasswordTextBox);
    
    //verifies login credentials
    fetch(url,{
        method: "POST",
        body: body,
        mode: "cors",
        credentials: "include",
        headers: {
            "Content-Type": 'application/x-www-form-urlencoded'
        }
    }).then(function (response){
        //what happens in successful login
        if(response.status == '303'){
            //switch over to assignment3 stuff
            registration.style.display = "none";
            buttons.style.display = "flex";

            var javaScript2 = document.createElement("script");
            javaScript2.src = "brains.js";
            javaScript2.type = "text/javascript";
            javaScript2.id = "script2";
            document.getElementsByTagName("body")[0].appendChild(javaScript2);
            document.getElementById('script').removeElement;           
        }
        //what happens in failed login
        if(response.status == '401'){
            alert("Your username and/or password are incorrect. Please try again.")
        }    
  })

 
}