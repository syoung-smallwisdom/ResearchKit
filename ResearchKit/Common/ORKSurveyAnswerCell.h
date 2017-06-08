/*
 Copyright (c) 2015, Apple Inc. All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:
 
 1.  Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 2.  Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation and/or
 other materials provided with the distribution.
 
 3.  Neither the name of the copyright holder(s) nor the names of any contributors
 may be used to endorse or promote products derived from this software without
 specific prior written permission. No license is granted to the trademarks of
 the copyright holders even if such marks are included in this software.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


@import UIKit;
#import "ORKTableViewCell.h"
#import <ResearchKit/ORKTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class ORKQuestionStep;
@class ORKSurveyAnswerCell;

ORK_CLASS_AVAILABLE
@protocol ORKSurveyAnswerCellDelegate

@required
- (void)answerCell:(ORKSurveyAnswerCell *)cell answerDidChangeTo:(id)answer dueUserAction:(BOOL)dueUserAction;
- (void)answerCell:(ORKSurveyAnswerCell *)cell invalidInputAlertWithMessage:(NSString *)input;
- (void)answerCell:(ORKSurveyAnswerCell *)cell invalidInputAlertWithTitle:(NSString *)title message:(NSString *)message;

@end

ORK_CLASS_AVAILABLE
@interface ORKSurveyAnswerCell : ORKTableViewCell {
@protected
    id _answer;
}

/**
 * This method should only be used by sub-classes, as it internally sets the answer
 * that must align with the expected answer type
 * It also triggers a call to the answerDidChangeTo delegate method
 */
- (void)ork_setAnswer:(id)answer;

/**
 * Expose validity alert message to allow for custom alert messaging
 */

- (void)showValidityAlertWithMessage:(NSString *)text;

/**
 * Expose validity alert message to allow for custom alert messaging
 */
- (void)showValidityAlertWithTitle:(NSString *)title message:(NSString *)message;

/*
 * This method is used to force the SurveyAnswerCell to reassess it's answer value
 */
- (void)answerDidChange;

- (instancetype)initWithStyle:(UITableViewCellStyle)style
              reuseIdentifier:(NSString *)reuseIdentifier
                         step:(ORKQuestionStep *)step
                       answer:(id)answer
                     delegate:(id<ORKSurveyAnswerCellDelegate>)delegate;

@property (nonatomic, weak, nullable) ORKQuestionStep *step;

@property (nonatomic, weak, nullable) id<ORKSurveyAnswerCellDelegate> delegate;

@property (nonatomic, copy, nullable) id answer;

// Gives an opportunity for cells to prevent navigation if the value has not been set
- (BOOL)shouldContinue;

@end

@interface ORKSurveyAnswerCell (ORKSurveyAnswerCellInternal)

- (void)prepareView;

+ (CGFloat)suggestedCellHeightForView:(UIView *)view;

- (NSArray *)suggestedCellHeightConstraintsForView:(UIView *)view;

+ (BOOL)shouldDisplayWithSeparators;

// Get full width layout for some subclass cells
+ (NSLayoutConstraint *)fullWidthLayoutConstraint:(UIView *)view;

@end


NS_ASSUME_NONNULL_END
