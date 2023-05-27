function encrypt(input, text, workerCount){
    let charactersPerWorker = [];
    countCharactersPerWorker(charactersPerWorker, input, workerCount);
    
    const workers = [];
    const encryptedText = [];
    
    checkAvailability(input,text);

    for(let i=0;i<workerCount;i++){
        const worker = new Worker('workerEncrypt.js');

        worker.onmessage = function(event) {
            const rowIndex = event.data[0];
            const colIndex = event.data[1];
            const charIndex = event.data[2];

            encryptedText[charIndex] = [rowIndex, colIndex];

            //Check if all workers have finished
            if(encryptedText.length === input.length){
                const inputElement = document.querySelector('#displayInput');
                inputElement.textContent = input;
                const result = document.querySelector('#displayResult');
                result.textContent = encryptedText.join(' ');
                const status = document.querySelector('#displayStatus');
                status.textContent = 'Encrypted';
            }
        };

        worker.postMessage([input, charactersPerWorker, text, i]);

        //Add the worker to the array
        workers.push(worker);
    }
}

function countCharactersPerWorker(array, characters, workerCount){
    let charCount;
    let reminder;
    if(characters.length < workerCount){
        workerCount = characters.length;
        charCount = 1;
    }else{
        charCount = Math.floor(characters.length / workerCount);
        reminder = characters.length % workerCount;
    }

    for(let i=0;i<workerCount;i++){
        let characterPerWorker = 0;
        if(reminder > 0){
            characterPerWorker++;
            reminder--;
        }
        array.push(charCount+characterPerWorker);
    }
}

function checkAvailability(input,text){
    let found;
    for(let i=0;i<input.length;i++){
        found = false;
        for(let j=0;j<text.length;j++){
            if(text[j] == input[i]){
                found = true;
                console.log('oki' + text[j]);
                break;
            }
        }
        if(!found){
            const inputElement = document.querySelector('#displayInput');
            inputElement.textContent = 'One ore more characters not found!';
            const result = document.querySelector('#displayResult');
            result.textContent = 'Couldn\'t encode!';
            const status = document.querySelector('#displayStatus');
            status.textContent = 'Couldn\'t encode!';
            throw new Error('');
        }
    }
}