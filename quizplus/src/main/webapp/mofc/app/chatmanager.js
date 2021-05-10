quizRunnerModule.factory('ChatManager', function(Storage, QuestionData) {
  var helper = Storage.getChat();
  
  const HEWITT = "What da ya want? I don't know anythin about no jewels. Look around if you want to, I'll tell you what I know.";
  const AGATHA = "You better find my jewels, else I'm calling Holmes. Now stop bothering me, I have to get my beauty sleep.";
  const DYLL = "These numbers don't add up - where is all the money? Something fishy is afoot - maybe you can find it.";
  const WANDA = "I just joined a week ago. My mistress is a cruel lady, she berates me so. I can help you, but I must cook first.";

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
        [makeMessage(HEWITT, suspects[0])],
        [makeMessage(AGATHA, suspects[1])],
        [makeMessage(DYLL, suspects[2])],
        [makeMessage(WANDA, suspects[3])],
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
  helper.getResponse = function(key) {
    return "Blah";
  };
  
  return helper;
});