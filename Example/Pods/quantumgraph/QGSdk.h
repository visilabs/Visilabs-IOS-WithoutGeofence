//
//  QGSdk.h
//  QGSdk
//
//  Created by QuantumGraph
//  Copyright (c) 2015 QuantumGraph. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>

@interface QGSdk : NSObject

/*!
 @abstract
 Flush timer's interval.
 
 @discussion
 Setting a flush interval of 0 will turn off the flush timer.
 
 @note Default to 1 sec in DEBUG and 15 secs in Release
 */
@property (atomic) NSUInteger flushInterval;

/*!
 @discussion
 Initialises QGSdk and returns the shared instance of the sdk,
 to access all the methods of the sdk
 
 @result QGSdk instance
 */
+ (QGSdk *) getSharedInstance;

/*!
 @abstract
 Set the app id and profile to setup sdk
 
 @discussion
 This initialises the sdk with your app id.
 Add this method to you AppDelegate applicaiton:didFinishLaunchingWithOptions:
 You can find it your account on app.qgraph.io in setup.
 
 @param appId           your QGraph account appId
 @param devProfile      True/Yes for Development and False/No for Production
 */
- (void)onStart:(NSString *)appId setDevProfile:(BOOL)devProfile;

/*!
 @abstract
 Set the app id, app group and profile to setup sdk
 
 @discussion
 Same as 'onStart:setDevProfile' with App Group options.
 Use this onStart method if you wish to add Widget extension of QGraph.
 App Group will help to share data between app target and widget target.
 App Group is 'Required' to log events from widget.
 
 @param appId           your QGraph account appId
 @param appGroup        APP-GROUP used for the widget and app target
 @param devProfile      True/Yes for Development and False/No for Production
 
 @note Pass appGroup as 'nil' if not using widget
 */
- (void)onStart:(NSString *)appId withAppGroup:(NSString *)appGroup setDevProfile:(BOOL)devProfile;

/*! This method is not used currently */
- (void)onStop;

/*!
 @abstract
 Sends the APNS token to QGraph Server
 
 @discussion
 Set the Device Token received from APNS in the AppDelegate.
 This method is required to identify device for sending push notification.
 
 @note Implement this in @code application:didRegisterForRemoteNotificationsWithDeviceToken: @endcode to setToken
 */
- (void)setToken:(NSData *)tokenData;

/*!
 @abstract
 Set the unique user id for your users
 
 @discussion
 you can identify your user with user_id while creating segment on app.qgraph.io
 */
- (void)setUserId:(NSString *)userId;

/*! @abstract Set the name of the user */
- (void)setName:(NSString *)name;

/*! @abstract Set the first name of the user */
- (void)setFirstName:(NSString *)name;

/*! @abstract Set the last name of the user */
- (void)setLastName:(NSString *)name;

/*! @abstract Set the city of the user */
- (void)setCity:(NSString *)city;

/*! @abstract Set the email id of the user */
- (void)setEmail:(NSString *)email;

/*! @abstract Set the day of DOB of the user */
- (void)setDayOfBirth:(NSNumber *)day;

/*! @abstract Set the month of DOB of the user */
- (void)setMonthOfBirth:(NSNumber *)month;

/*! @abstract Set the year of DOB of the user */
- (void)setYearOfBirth:(NSNumber *)year;

/*!
 @abstract
 Set any custom key for your user
 
 @discussion
 Use this method to set any custom key for the user.
 Suppose you want to set rating of the user.
 
 @code setCustomKey:@"rating" withValue:3.5 @endcode
 */
- (void)setCustomKey:(NSString *)key withValue:(id)value;

/*!
 @abstract
 Sends any event in your app to the QGraph server
 
 @discussion
 This methods help you track any particular event.
 for example, viewing the products, playing a game or listening to a music
 
 eg: logEvent:@"product_viewed"
 
 @param name            name of the event
 */
- (void)logEvent:(NSString *)name;

/*!
 @abstract
 Track any event in your app with custom parameter
 
 @discussion
 Same as logEvent: but with some parameter in form of dictionary.
 You can pass custom parameter for the particular event.
 
 eg: for event: product_viewed, you want to track name of the product, brand, image url or any other details.
 
 @note use valid data types in dictionary
 
 @param name            name of the event
 @param parameters      dictionary of all the parameter for the event
 */
- (void)logEvent:(NSString *)name withParameters:(NSDictionary *)parameters;

/*!
 @abstract
 Track any event in your app with monetary value associated to it
 
 @discussion
 eg: for event: product_viewed, price of the product is Rs 50
 
 @note Use value in the form of NSNumber
 
 @param name            name of the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 */
- (void)logEvent:(NSString *)name withValueToSum:(NSNumber *)valueToSum;

/*!
 @abstract
 Track any event in your app with monetary value associated to it along with its currency
 
 @discussion
 eg: for event: product_viewed, price of the product is 50 INR or 1 USD
 
 @note Use value in the form of NSNumber and 3 character currency code
 
 @param name            name of the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 @param vtsCurr         currency code of the value to sum
 */
- (void)logEvent:(NSString *)name withValueToSum:(NSNumber *)valueToSum withValueToSumCurrency:(NSString *)vtsCurr;

/*!
 @abstract
 Track any event in your app with custom parameters and monetary value associated to it
 
 @discussion
 Combination of logEvent:withParameter and logEvent:valueToSum
 
 @param name            name of the event
 @param parameters      dictionary of all the parameter for the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 */
- (void)logEvent:(NSString *)name withParameters:(NSDictionary *)parameters withValueToSum:(NSNumber *) valueToSum;

/*!
 @abstract
 Track any event in your app with custom parameters and monetary value associated to it along with its currency
 
 @discussion
 Combination of logEvent:withParameter and logEvent:withValueToSum:withValueToSumCurrency
 
 @param name            name of the event
 @param parameters      dictionary of all the parameter for the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 @param vtsCurr         currency code of the value to sum
 */
- (void)logEvent:(NSString *)name withParameters:(NSDictionary *)parameters withValueToSum:(NSNumber *) valueToSum withValueToSumCurrency:(NSString *)vtsCurr;

/*!
 @abstract
 Sets the Click Through Attribution Window for event attribution
 
 @discussion
 This method should be used to set the click through attribution window.
 Click through works for push notification (sent by QGraph) clicks and InApp Notification clicks.
 Default to 24 hrs (86400 secs).
 
 eg: for click attribution window to be 12 hrs, pass the value: 43200
 
 @note Pass seconds as '0' to disable click attribution
 
 @param seconds         attribution window time in seconds
 */
- (void)setClickAttributionWindow:(NSInteger)seconds;

/*!
 @abstract
 Sets the View Through Attribution Window for event attribution
 
 @discussion
 This method should be used to set the View through attribution window.
 View through attribution works only for InApp notifications.
 Default to 1 hr (3600 secs).
 
 eg: for view through attribution window to be 2 hrs, pass the value: 7200
 
 @note Pass seconds as '0' to disable view through attribution
 
 @param seconds         attribution window time in seconds
 */
- (void)setAttributionWindow:(NSInteger)seconds;

/*!
 @abstract
 Disables In-App campaigns
 
 @discussion
 This method allows to enable and disable InApp campaigns to be delivered to device
 By default it is enabled, set 'YES' to disable it
 Disabling it will prevent device to get any new InApp Campaigns
 
 @note Use @code disableInAppCampaigns:YES @endcode to Disable
 */
- (void)disableInAppCampaigns:(BOOL)disabled;

/*!
 @abstract
 Disables user conversion tracking between web apps and iOS apps
 
 @discussion
 Used for User Conversion Tracking between web apps and ios apps using safari cookies
 If you want to disable user tracking and reading cookies in safari, use this method
 
 By Default, it is enabled. Call it in your <b>AppDelegate</b>, only to 'DISABLE'
 
 */
- (void)disableUserTrackingForSafari;


/*!
 @abstract
 Tracks application launch finish
 
 @discussion
 Add this method to your AppDelegate applicaiton:didFinishLaunchingWithOptions:
 */
- (void)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

/*!
 @abstract
 Captures the push notification sent by QGraph server
 
 @discussion
 Add to your AppDelegate application:didReceiveRemoteNotification:fetchCompletionHandler:
 pass all the push notifications received by the app
 This method also let the sdk track app_launched event due to click on the notification sent by QGraph
 */
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

/*!
 @abstract
 Returns Action Category for Custom Carousel Push
 
 @discussion
 Push Notification Action Category for Custom Carousel Push sent by QGraph for iOS 10.
 
 To Register your action category, create other categories, if any.
 Create NSSet with all the action categories and set it to the UNNotificationCenter
 
 Pass button titles as nil to use the default title.
 
 @note
 Please add @code #import <UserNotifications/UserNotifications.h> @endcode in your AppDelegate
 or the class you would like to add it.
 Import <b>UserNotifications.framework</b> in your app target.
 Also add <b>UNNotificationCenterDelegate</b> to your Class
 
 @param next            Next Button Title, default '▶▶'
 @param openApp         Open App Button Title, default 'GO TO APP'
 
 @code
 UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
 UNNotificationCategory *qgCategory = [[QGSdk getSharedInstance] getQGSliderPushActionCategoryWithNextButtonTitle:@"▶▶" withOpenAppButtonTitle:@"GO TO APP"];
 NSSet *categories = [NSSet setWithObjects:qgCategory,..., nil];
 [center setNotificationCategories:categories];
 @endcode
*/
- (UNNotificationCategory *)getQGSliderPushActionCategoryWithNextButtonTitle:(NSString *)next withOpenAppButtonTitle:(NSString *)openApp;

/*!
 @abstract
 Captures the push notification delivered in foreground.
 
 @discussion
 Add to your AppDelegate or class implementing your UNNotificationCenterDelegate methods.
 @code
 [[QGSdk getSharedInstance] userNotificationCenter:center willPresentNotification:notification];
 @endcode
 
 The delegate method can be used to show the notification alert in the foreground State.
 In your completion handler, pass your UNNotificationPresentationOptions.
 
 For eg:
 @code
 UNNotificationPresentationOptions option = UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionSound | UNNotificationPresentationOptionAlert;
 completionHandler(option);
 @endcode
 
 */
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification;

/*!
 @abstract
 Captures the push notification clicked event.
 
 @discussion
 Add to your AppDelegate or class implementing your UNNotificationCenterDelegate methods.
 
 The method will be called on the delegate when the user responded to the notification by opening the application or choosing a UNNotificationAction.
 
 @code
 [[QGSdk getSharedInstance] userNotificationCenter:center didReceiveNotificationResponse:response];
 @endcode
 */
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response;

/*!
 @abstract
 Uploads queued data to the QGraph server.
 
 @discussion
 By default, queued data is flushed to the QGraph servers every 15 seconds (the
 default for flushInterval). You only need to call this
 method manually if you want to force a flush at a particular moment.
 */
- (void)flush;

/*!
 @abstract
 Calls flush, then calls a handler when finished.
 
 @discussion
 When calling flush manually, it is sometimes important to verify
 that the flush has finished before further action is taken.
 */
- (void)flushWithCompletion:(void (^)())handler;

@end
