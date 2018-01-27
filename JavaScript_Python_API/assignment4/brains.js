//initial setup
var url = 'http://127.0.0.1:8080/entries';

var buttons           = document.getElementById('buttons');
var createButton      = document.getElementById('createButton');
var retrieveAllButton = document.getElementById('retrieveAllButton');
var retrieveOneButton = document.getElementById('retrieveOneButton');
var updateButton      = document.getElementById('updateButton');
var deleteButton      = document.getElementById('deleteButton');
var text              = document.getElementById('text');
var textBox           = document.getElementById('textBox');
var bodyTable         = document.getElementById('bodyTable');

var description      = "";
var priority         = -1; 
var dueDate          = "";
var inputBy          = ""; 
var reminder         = -1;
var repeated         = -1;
var tempItemReminder = "";
var tempItemRepeater = "";

var createReappear      = 0;
var retrieveOneReappear = 0;
var updateReappear      = 0;
var deleteReappear      = 0;

var path           = "";
var retrieveOneUrl = "";
var updateUrl      = "";
var deleteUrl      = "";



//showtime
window.onload = function(){fetch(url).then(checkstatus)};





//createButton function
createButton.onclick = function(){
    if(createReappear == 0){
        textBox.value = "";
        text.appendChild(createButton);
        textBox.placeholder = "Enter Description";
        document.body.style.backgroundColor = "#dcfff8";
        createButton.innerHTML = "Submit";
        buttons.style.display = "none";
        text.style.display = "flex";
    }
    if(createReappear == 1){
        description = textBox.value;
        textBox.value = "";
        textBox.placeholder = "Enter Priority";
    }
    if(createReappear == 2){
        priority = parseInt(textBox.value);
        textBox.value = "";
        textBox.placeholder = "Enter Due Date";
    }
    if(createReappear == 3){
        dueDate = textBox.value;
        textBox.value ="";
        textBox.placeholder = "Enter Originator";
    }
    if(createReappear == 4){
        inputBy = textBox.value;
        textBox.value = "";
        textBox.placeholder = "Do you want a reminder? (Y/N)";
    }
    if(createReappear == 5){
        tempItemReminder = textBox.value;
        if(tempItemReminder == "y" || tempItemReminder == "Y"){
            reminder = 1;
        }
        else{
            reminder = 0;
        }
        textBox.value = "";
        textBox.placeholder = "Do you want a repeat? (Y/N)";
        createButton.innerHTML = "Create";
    }
    if(createReappear == 6){
        tempItemRepeater = textBox.value;
        if(tempItemRepeater == "y" || tempItemRepeater == "Y"){
            repeated = 1;
        }
        else{
            repeated = 0;
        }
        buttons.appendChild(createButton);
        document.body.style.backgroundColor = "#fff8dc";
        buttons.style.display = "flex";
        text.style.display = "none";
        
        //grabs all textbox contents and encode
        var body = "description="  + encodeURIComponent(description) + 
                   "&priority="    + encodeURIComponent(priority) +  
                   "&dueDate="     + encodeURIComponent(dueDate) +  
                   "&inputBy="     + encodeURIComponent(inputBy) +
                   "&reminder="    + encodeURIComponent(reminder) +
                   "&repeated="    + encodeURIComponent(repeated);

        //fetch POST
        fetch(url,{
            method: "POST",
            body: body,
            mode: "no-cors",
            headers: {
                "Content-Type": 'application/x-www-form-urlencoded'
            }
        });
    }
    
    createReappear++;
    if(createReappear == 7){
        createReappear = 0;
        var itemList = [priority, description, dueDate, inputBy, reminder, repeated];
        addTodo(itemList);
    }
    
}





//retrieveAllButton
retrieveAllButton.onclick = function(){
    clearTable();
    fetch(url)
    .then((resp) => resp.json())
    .then(function(data){
        for(i = 0; i < data.length; i++){
            addTodo(data[i]);
        }
    });
}






//retrieveOneButton
retrieveOneButton.onclick = function(){
    if(retrieveOneReappear == 0){
        document.body.style.backgroundColor = "#dce3ff";
        textBox.value = "";
        text.appendChild(retrieveOneButton);
        textBox.placeholder = "Enter the number of the item";
        buttons.style.display = "none";
        text.style.display = "flex";
    }
    if(retrieveOneReappear == 1){
        description = parseInt(textBox.value);
        document.body.style.backgroundColor = "#fff8dc";
        buttons.style.display = "flex";
        text.style.display = "none";
        buttons.appendChild(retrieveOneButton);
        path = '/' + description.toString();
        retrieveOneUrl = url + path;
        
        fetch(retrieveOneUrl)
        .then((resp) => resp.json())
        .then(function(data){
            clearTable();
            addTodo(data[0]);
        });
    }
    retrieveOneReappear++;
    if(retrieveOneReappear == 2){
        retrieveOneReappear = 0;
    }
}






//updateButton function
updateButton.onclick = function(){
    if(updateReappear == 0){
        document.body.style.backgroundColor = "#ffe990";
        textBox.value = "";
        text.appendChild(updateButton);
        updateButton.innerHTML = "Select";
        textBox.placeholder = "Enter the number of the item";
        buttons.style.display = "none";
        text.style.display = "flex";
    }
    if(updateReappear == 1){
        description = parseInt(textBox.value);
        textBox.value ="";
        textBox.placeholder = "Enter New Description";
        updateButton.innerHTML = "Update";
    }
    if(updateReappear == 2){
        var newDescription = textBox.value;
        buttons.appendChild(updateButton);
        document.body.style.backgroundColor = "#fff8dc";
        buttons.style.display = "flex";
        text.style.display = "none";
        path = '/' + description.toString();
        updateUrl = url + path;
        
        //grabs all textbox contents and encode
        var body = "description="      + encodeURIComponent(description) + 
                    "&newDescription=" + encodeURIComponent(newDescription);

        //fetch PUT
        fetch(updateUrl,{
            method: "PUT",
            body: body,
            mode: "cors",
            headers: {
                "Content-Type": 'application/x-www-form-urlencoded'
            }
        });
    }
    updateReappear++;
    if(updateReappear == 3){
        updateReappear = 0;
    }
}






//deleteButton function
deleteButton.onclick = function(){
    if(deleteReappear == 0){
        text.appendChild(deleteButton);
        document.body.style.backgroundColor = "#ffdce3";
        textBox.value = "";
        textBox.placeholder = "Enter the number of the item";
        buttons.style.display = "none";
        text.style.display = "flex";
    }
    if(deleteReappear == 1){
        description = parseInt(textBox.value);
        document.body.style.backgroundColor = "#fff8dc";
        buttons.style.display = "flex";
        text.style.display = "none";
        buttons.appendChild(deleteButton);
        
        path = '/' + description.toString();
        updateUrl = url + path;
        
        //grabs all textbox contents and encode
        var body = "id="      + encodeURIComponent(description);

        //fetch POST
        fetch(updateUrl,{
            method: "DELETE",
            body: body,
            mode: "cors",
            headers: {
                "Content-Type": 'application/x-www-form-urlencoded'
            }
        });
    }
    deleteReappear++;
    if(deleteReappear == 2){
        deleteReappear = 0;
    }
}





//function to check status of server
var checkstatus = function(response){
    if(response.status >= 200 && response.status < 300){
        console.log("Status code good.");
    }else {
        console.log("Status code not good.")
    }
}






var addTodo = function(itemList){
    var tr            = document.createElement('tr');
    
    var tdPriority    = document.createElement('td');
    var tdDescription = document.createElement('td');
    var tdDueDate     = document.createElement('td');
    var tdInputBy     = document.createElement('td');
    var tdReminder    = document.createElement('td');
    var tdRepeated    = document.createElement('td');

    if(itemList[5] == 1){
        tempItemReminder = "yes";
 
    }else{
        tempItemReminder = "no";
    }
    if(itemList[6] == 1){
        tempItemRepeater = "yes";
 
    }else{
        tempItemRepeater = "no";
    }
    
    var textPriority = document.createTextNode(itemList[2]);
    var textDescription = document.createTextNode(itemList[1]);
    var textDueDate = document.createTextNode(itemList[3]);
    var textInputBy = document.createTextNode(itemList[4]);
    var textReminder = document.createTextNode(tempItemReminder);
    var textRepeated = document.createTextNode(tempItemRepeater);
    
    tr.className = "tableRow";
    
    tdPriority.appendChild(textPriority);
    tr.appendChild(tdPriority);
    bodyTable.appendChild(tr);
    
    tdDescription.appendChild(textDescription);
    tr.appendChild(tdDescription);
    bodyTable.appendChild(tr);
    
    tdDueDate.appendChild(textDueDate);
    tr.appendChild(tdDueDate);
    bodyTable.appendChild(tr);
    
    tdInputBy.appendChild(textInputBy);
    tr.appendChild(tdInputBy);
    bodyTable.appendChild(tr);
    
    tdReminder.appendChild(textReminder);
    tr.appendChild(tdReminder);
    bodyTable.appendChild(tr);
    
    tdRepeated.appendChild(textRepeated);
    tr.appendChild(tdRepeated);
    bodyTable.appendChild(tr);
    
}
 var clearTable = function(){
     for(var i = 1; i < bodyTable.rows.length;){
            bodyTable.deleteRow(i);
     }
 }