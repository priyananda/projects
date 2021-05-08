quizRunnerModule.factory('ChatManager', function(Storage, QuestionData) {
  var helper = Storage.getChat();
  
  function makeMessage(messageText, author) {
    const timestamp = Date.now();
    return {
        id: timestamp,
        text: messageText,
        userName: author.name,
        userId: author.id,
        avatar: author.image,
        date: timestamp
      };
  }
  
  function initChat() {
    var suspects = QuestionData.getSuspects();
    return {
      messages: [
        [makeMessage("Hello there 1!", suspects[0])],
        [makeMessage("Hello there 2!", suspects[1])],
        [makeMessage("Hello there 3!", suspects[2])],
        [makeMessage("Hello there 4!", suspects[3])],
      ]
    }
  }
  
  if (!helper) {
    helper = initChat();
    Storage.saveChat(helper);
  }
 
  helper.getMessages = function(channelId) {
    return helper.messages[channelId - 1];
  };
  helper.addMessage = function(channelId, messageText, author){
    helper.messages[channelId - 1].push(makeMessage(
        messageText, author));
    Storage.saveChat(helper);
  };
  
  return helper;
});