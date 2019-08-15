var database = firebase.database().ref();
var form = document.getElementById("form");
document.getElementById("add-message-btn").addEventListener("click", addMessageBtnClicked);


function pushMessage(name, message, date){
    var messageRef = database.child("messages");
    var newMessage = messageRef.push();
    newMessage.set({
        name: name,
        message: message,
        date: date
    })
}

function queueMessages(name, message, date){
    var queueMessageRef = database.child("queueMessages");
    var queueMessage = queueMessageRef.push();
    queueMessage.set({
        name: name,
        message: message,
        data: date
    })
}
function getTimestamp(){
    // Date class variables
    var monthNames = [
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
    ];
    var daysOfWeek = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
    var currentDate = new Date();
    var date = currentDate.getDate();
    var month = currentDate.getMonth(); // January is 0 not 1
    var year = currentDate.getFullYear();
    var hour = currentDate.getHours();
    var minutes = currentDate.getMinutes();
    var seconds = currentDate.getSeconds();
    var ordinalDate = monthNames[month] + " " + date + ", " + year;
    var time = hour + ":" + minutes + ":" + seconds;
    var timestamp = daysOfWeek[currentDate.getDay()] + ", " + ordinalDate + " " + time;
    console.log(timestamp);
    return timestamp;
}


function verifyForm(name, message){
    if (name.length === 0 || message.length === 0){
        return false;
    } else return true;
}

function displaySuccess() {
    var modal = document.getElementById("successModal");
    var span = document.getElementsByClassName("close")[0];
    modal.style.display = "block";
    span.onclick = function() {
        modal.style.display = "none";
        window.onclick = function(event) {
            if (event.target == modal) {
                modal.style.display = "none";
            }
        };
    };
}

function addMessageBtnClicked() {
    let nameDOM = document.getElementById("name").value;
    let messageDOM = document.getElementById("message").value;
    var timestamp = getTimestamp();
    var verify = verifyForm(nameDOM, messageDOM);
    console.log("name: " + nameDOM + " messsage: " + messageDOM + " time: " + timestamp);
    console.log(verify);

    if (verify === true){
        pushMessage(nameDOM, messageDOM, timestamp);
        displaySuccess();
        form.reset();
    } else {
        alert("You have missing info :(");
    }
}




