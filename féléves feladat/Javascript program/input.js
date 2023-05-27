//Encrypt elements
const inputEncrypt = document.querySelector('#inputFieldEncrypt');
const buttonEncrypt = document.querySelector('#inputButtonEncrypt');

inputEncrypt.addEventListener('keydown', handleInputFieldEnter.bind(inputEncrypt));
buttonEncrypt.addEventListener('click', handleButtonClick.bind(buttonEncrypt));

//Decrypt elements
const inputDecrypt = document.querySelector('#inputFieldDecrypt');
const buttonDecrypt = document.querySelector('#inputButtonDecrypt');

inputDecrypt.addEventListener('keydown', handleInputFieldEnter.bind(inputDecrypt));
buttonDecrypt.addEventListener('click', handleButtonClick.bind(buttonDecrypt));

//Handle input on Enter
function handleInputFieldEnter(event){
    
    if(event.key === 'Enter'){
        const inputText = this.value;
        const inputField = document.querySelector('#' + this.id);
        const status = document.querySelector('#displayStatus');
        inputField.value = '';

        //Decrypt field input
        if(this.id === 'inputFieldDecrypt'){
            if(inputText.trim() != ''){
                if(checkFormat(inputText)){
                    const displayInput = document.querySelector('#displayInput');
                    getText(inputText, this.id); 
                    displayInput.textContent = inputText;
                    status.textContent = 'Decrypted';
                }else{
                    status.textContent = 'Incorrect input format!';
                    const input = document.querySelector('#displayInput');
                    const result = document.querySelector('#displayResult');
                    input.textContent = '';
                    result.textContent = '';
                }
            }else{
                status.textContent = 'Input can\'t be empty!';
                const input = document.querySelector('#displayInput');
                const result = document.querySelector('#displayResult');
                input.textContent = '';
                result.textContent = '';
            }
        //Encrypt field input
        }else if(this.id == 'inputFieldEncrypt'){
            if(inputText != ''){
                const displayInput = document.querySelector('#displayInput');
                getText(inputText, this.id);
                displayInput.textContent = inputText;
                //status.textContent = 'Encrypted';
            }else{
                status.textContent = 'Input can\'t be empty!';
                const input = document.querySelector('#displayInput');
                const result = document.querySelector('#displayResult');
                input.textContent = '';
                result.textContent = '';
            }
        }
    }

}

//Handle input with button click
function handleButtonClick(){
    const inputField = document.querySelector('#inputFieldDecrypt');
    const status = document.querySelector('#displayStatus');
    const inputText = inputField.value;
    inputField.value = '';

    //Decrypt button input
    if(this.id == 'inputButtonDecrypt'){
        
        if(inputText.trim() != ''){
            const correctFormat = checkFormat(inputText);
            
            if(correctFormat){
                const displayInput = document.querySelector('#displayInput');
                getText(inputText, inputField.id);
                displayInput.textContent = inputText;
                status.textContent = 'Decrypted';
            }else{
                status.textContent = 'Incorrect input format!';
                const input = document.querySelector('#displayInput');
                const result = document.querySelector('#displayResult');
                input.textContent = '';
                result.textContent = '';
            }
        }else{
            status.textContent = 'Input can\'t be empty!';
            const input = document.querySelector('#displayInput');
            const result = document.querySelector('#displayResult');
            input.textContent = '';
            result.textContent = '';
        }
    //Encrypt button input
    }else if(this.id == 'inputButtonEncrypt'){
        const inputField = document.querySelector('#inputFieldEncrypt');
        const inputText = inputField.value;
        inputField.value = '';
        
        if(inputText != ''){
            const displayInput = document.querySelector('#displayInput');
            getText(inputText, inputField.id);
            displayInput.textContent = inputText;
        }else{
            status.textContent = 'Input can\'t be empty!';
            const input = document.querySelector('#displayInput');
            const result = document.querySelector('#displayResult');
            input.textContent = '';
            result.textContent = '';
        }
    }
}

//Check whether the code to be decrypted has correct format
function checkFormat(input){
    
    const pattern = /^(\d+,\d+\s)*\d+,\d+$/;
    const isCorrectFormat = pattern.test(input);

    return isCorrectFormat;
}