//
//  W2STSDKFeatureAutoConfigurable.h
//  W2STApp
//
//  Created by Giovanni Visentini on 13/04/15.
//  Copyright (c) 2015 STMicroelectronics. All rights reserved.
//

#import "W2STSDKFeature.h"

@protocol W2STSDKFeatureAutoConfigurableDelegate;

/**
 *  extend a feature adding the possibility to have a self configuration routine
 * that run on the node. this routine can be start/stop or query by this type of
 * feature.
 *
 */
@interface W2STSDKFeatureAutoConfigurable : W2STSDKFeature

/**
 *  true if the feature is configurated
 */
@property(readonly) BOOL isConfigurated;

/**
 *  run the self configuration routine in the node
 *
 *  @return true if the message is correctly send
 */
-(BOOL) startAutoConfiguration;

/**
 *  request the status of the configuration process, the status is an int between
 * 0 and 100.
 * the status is notify using the didAutoConfigurationChange delegate callback
 *
 *  @return true if the message is correctly send
 */
-(BOOL) requestAutoConfigurationStatus;

/**
 * request to stop the self configuration process
 *
 *  @return true if the message is correctly send
 */
-(BOOL) stopAutoConfiguration;

/**
 *  register a delegate for this feature
 * 
 * Note that the callback are done by an concurrent queue
 *
 *  @param delegate object where notify the configuration change
 */
-(void) addFeatureConfigurationDelegate:(id<W2STSDKFeatureAutoConfigurableDelegate>)delegate;

/**
 *  remove a delegate for this feature
 *
 *  @param delegate delegate to remove
 */
-(void) removeFeatureConfigurationDelegate:(id<W2STSDKFeatureAutoConfigurableDelegate>)delegate;

@end

/**
 *  protocol used for notify the change configuration change
 */
@protocol  W2STSDKFeatureAutoConfigurableDelegate <NSObject>

/**
 *  method called when the node notify that the configuration routine start
 *
 *  @param feature feature that start the auto configuration process
 */
@optional -(void)didAutoConfigurationStart:(W2STSDKFeatureAutoConfigurable *)feature;


/**
 *  method called when the node notify a change in the configuration status
 *
 *  @param feature feature that send the message
 *  @param status  number between 0 to 100
 */
@optional -(void)didAutoConfigurationChange:(W2STSDKFeatureAutoConfigurable *)feature
                                     status:(int32_t)status;


/**
 *  method called when the node notify that the configuration routine ends
 *
 *  @param feature feature that finished the configuration
 *  @param status last configuration status
 */
@optional -(void)didConfigurationFinished:(W2STSDKFeatureAutoConfigurable *)feature
                          status:(int32_t)status;
@end